window.addEventListener("load",function() 
	{
	//////////////////////////////////////////////////////////////////////////
	// Quintus engine
	//////////////////////////////////////////////////////////////////////////
	//var Q = Quintus({audioSupported: [ 'wav','mp3','ogg' ]});
	var Q = Quintus({audioSupported: [ 'mp3' ]});
	Q.include("Sprites, Scenes, Input, 2D, Anim, Touch, UI, TMX, Audio");  // Módulos que se usarán
	Q.setup({width:320, height:480});  // Configuración del canvas
	//Q.setup({ maximize: true });
	Q.controls().touch();
	Q.enableSound();
    // Control de colisiones
    Q.SPRITE_NONE = 0;
	Q.SPRITE_DEFAULT = 1;
    Q.SPRITE_PLAYER = 2;
	Q.SPRITE_COLLECTABLE = 4;
	Q.SPRITE_ENEMY = 8;
	Q.SPRITE_POWERUP = 16; 

	//////////////////////////////////////////////////////////////////////////
	// Mario
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Mario", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				sheet: "marioSmallR",  // la spritesheet para animar a 'Mario'
				sprite: "marioSmallR",  // el sprite básico de 'Mario'
				jumpSpeed: -400,  // la velocidad del salto de 'Mario' que nos proporciona 'platformerControls'
				type: Q.SPRITE_PLAYER,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_COLLECTABLE | Q.SPRITE_ENEMY
				});
			this.p.hitsPowerUp=false;  // Indica si 'Mario' ha golpeado una caja con 'PowerUp'
			this.p.marioSmall=true;  // Indica si 'Mario' es pequeño o grande
			this.p.onJump=true;  // Indica si 'Mario' está saltando durante el juego
			this.p.wentRight=true;  // Indica si 'Mario' fue hacia la derecha antes de pararse
			this.p.wentLeft=false;  // Indica si 'Mario' fue hacia la izquierda antes de pararse
			this.p.winJumpTime=false;  // Indica si 'Mario' va a saltar celebrando la victoria
			this.p.onGroundJumpTime=false;  // Indica si 'Mario' está en el suelo durante la celebración de la victoria
			this.p.currentSong='music_main.mp3';  // La canción que suena actualmente asociada a 'Mario'
			this.p.mainSong='music_main.mp3';  // Tema principal
			this.p.levelCompleteSong='music_level_complete.mp3';  // Tema de victoria
			this.p.deathSong='music_die.mp3';  // Tema de la muerte
			// 
			Q.audio.play(this.p.currentSong,{ loop: true });
			// Componentes
			this.add('2d, platformerControls, animation');
			// Eventos
			this.on("marioWins",function() 
				{
				// "marioWins" es un evento que triggeriza la princesa cuando llegamos a ella habiendo conseguido todo y hace que 'Mario' salte
				Q.audio.stop(this.p.currentSong);
				this.p.currentSong=this.p.levelCompleteSong;
				Q.audio.play(this.p.currentSong);
				this.p.winJumpTime=true;
				this.p.onGroundJumpTime=true;
				this.del('platformerControls');
				});
			this.on("marioLoses",function() 
				{
				// "marioWins" es un evento que triggeriza la princesa cuando llegamos a ella y no hemos conseguido todo
				Q.audio.stop(this.p.currentSong);
				this.p.currentSong=this.p.deathSong;
				Q.audio.play(this.p.currentSong);
				this.del('platformerControls');
				});
			this.on("marioGrows",function() 
				{
				// "marioGrows" es un evento que triggeriza la 'Mushroom' y hace que 'Mario' se haga grande
				Q.state.inc("powerups",1);
				Q.stages[1].trigger("powerUpCollected");
				this.p.marioSmall=false;
				this.p.sheet="marioLargeR";
				this.p.sprite="marioLargeR";
				this.p.cy=32;
				this.p.points[0][0]=-16; this.p.points[0][1]=-32;
				this.p.points[1][0]=16; this.p.points[1][1]=-32;
				this.p.points[2][0]=16; this.p.points[2][1]=32;
				this.p.points[3][0]=-16; this.p.points[3][1]=32;
				//***** reproducir sonido de powerUp
				});
			this.on("marioSuitsUp",function() 
				{
				// "marioSuitsUp" es un evento que triggeriza la 'Flower' y hace que 'Mario' se ponga blanco
				Q.state.inc("powerups",1);
				Q.stages[1].trigger("powerUpCollected");
				this.p.sheet="marioFireR";
				this.p.sprite="marioFireR";
				this.p.cy=32;
				this.p.points[0][0]=-16; this.p.points[0][1]=-32;
				this.p.points[1][0]=16; this.p.points[1][1]=-32;
				this.p.points[2][0]=16; this.p.points[2][1]=32;
				this.p.points[3][0]=-16; this.p.points[3][1]=32;
				//***** reproducir sonido de powerUp
				});
			this.on("bump.top",function(collision)
				{
				if (collision.obj.isA("TileLayer"))
					{
					switch (collision.tile)
						{
						case 37:  // Caja '?' cerrada
							console.log("Colisión con caja '?' cerrada ("+collision.tileX+","+collision.tileY+")");
							collision.obj.setTile(collision.tileX,collision.tileY, 23);
							posTileX=collision.tileX; posTileY=collision.tileY;
							Q.stages[0].trigger("checkPowerUp",{posTileX,posTileY});  // Comprobamos si hemos hecho hit en un powerUp
							if (this.p.hitsPowerUp)  // Si en la caja '?' hay un 'PowerUp'
								{
								this.p.hitsPowerUp=false;  // Evitamos que en la siguiente caja '?' crea que hay 'PowerUp'
								if (this.p.marioSmall)  // Si 'Mario' es pequeño sale una 'Mushroom'
									{
									mushroom=Q.stages[0].insert(new Q.Mushroom({x:(collision.tileX+0.5)*34,y:(collision.tileY+0.5)*34,z:-100}));
									mushroom.trigger("surpriseBox");
									}
								else  // Si 'Mario' es grande sale una 'Flower'
									{
									flower=Q.stages[0].insert(new Q.Flower({x:(collision.tileX+0.5)*34,y:(collision.tileY+0.5)*34,z:-100}));
									flower.trigger("surpriseBox");
									}
								}
							else // Si en la caja '?' hay una 'Coin'
								{
								coin=Q.stages[0].insert(new Q.Coin({x:(collision.tileX+0.5)*34,y:(collision.tileY)*34,z:-100}));
								coin.trigger("surpriseBox");
								}
							break;
						case 23:  // Caja '?' abierta
							console.log("Colisión con caja '?' abierta ("+collision.tileX+","+collision.tileY+")");
							// Sonido de tocar caja sin hacer nada
							break;
						case 44:  // Ladrillo
							console.log("Colisión con ladrillo ("+collision.tileX+","+collision.tileY+")");
							if (this.p.marioSmall)
								{								
								//***** reproducir sonido de tocar caja sin hacer nada	
								}
							else
								{
								//***** reproducir sonido de destruir ladrillo
								//***** destruir ladrillo	
								}
							break;
						default:
							console.log("Colisión con caja genérica ("+collision.tileX+","+collision.tileY+")");
							break;
						}
					} 
				});
			this.on("powerUpDiscovered",function()
				{
				// "powerUpDiscovered" es un evento que triggeriza la escena cuando descubrimos un 'PowerUp'
				this.p.hitsPowerUp=true;
				});
			this.on("bump.bottom",function(collision) 
				{
				// "bump.bottom" es un evento que triggerizan las colisiones por debajo de 'Mario'
				if (this.p.winJumpTime)  // Si 'Mario' toca el suelo en el salto de la victoria lo indicamos
					{
					this.p.onGroundJumpTime=true;
					}
				else  // Si 'Mario' está tocando el suelo y no es el salto de la victoria estamos jugando
					{
					this.p.onJump=false;	
					}
				});
			// Me suscribo a los eventos de entrada para cuando se presione 'up'
			Q.input.on("up",function()
				{
				if (!player.p.onJump)
					{
					Q.audio.play('jump_small.mp3');
					}
				});
			},

		step: function(dt)
			{
			// Si 'Mario' está en el aire se indica.
			if ((this.p.vy!=0) || (this.p.vy===0 && this.p.onJump))
				{
				player.p.onJump=true;
				}
			// Si 'Mario' se cae por el precipicio se reinicia el juego 
			if (this.p.y>600)
				{
				Q.clearStages();
				Q.audio.stop(this.p.currentSong);
				this.p.currentSong=this.p.deathSong;
				Q.audio.play(this.p.currentSong);
				Q.stageScene("startGame"); 
				}
			// Si 'Mario'está en el salto de la victoria es que llegó a la princesa
			if (this.p.winJumpTime)
				{
				if (this.p.onGroundJumpTime)
					{
					this.play("jumpRight");
					this.p.vx=0;
					this.p.vy=-400;
					this.p.onGroundJumpTime=false;
					}
				}
			// Si 'Mario' no está en el salto de la victoria es que está jugando aún
			else if (!this.p.winJumpTime)
				{
				// Si está saltando hacia la derecha
				if (this.p.vy!=0 && this.p.vx>0)
					{
					Q.stages[0].trigger("cameraFocus",false);
					this.p.wentRight=true; this.p.wentLeft=false;
					this.play("jumpRight");
					}
				// Si está saltando hacia la izquierda
				else if (this.p.vy!=0 && this.p.vx<0)
					{
					Q.stages[0].trigger("cameraFocus",true);
					this.p.wentLeft=true; this.p.wentRight=false;
					this.play("jumpLeft");
					}
				// Si está saltando hacia arriba y acaba de saltar hacia la derecha
				else if (this.p.vy!=0 && this.p.vx===0 && this.p.wentRight)
					{
					Q.stages[0].trigger("cameraFocus",false);
					this.play("jumpRight");
					}
				// Si está saltando hacia arriba y acaba de saltar hacia la izquierda
				else if (this.p.vy!=0 && this.p.vx===0 && this.p.wentLeft)
					{
					Q.stages[0].trigger("cameraFocus",true);
					this.play("jumpLeft");
					}
				// Si está corriendo hacia la derecha
				else if(this.p.vx>0) 
					{
					Q.stages[0].trigger("cameraFocus",false);
					this.p.wentRight=true; this.p.wentLeft=false;
					this.play("runRight");
					}
				// Si está corriendo hacia la izquierda
				else if(this.p.vx<0)
					{
					Q.stages[0].trigger("cameraFocus",true);
					this.p.wentLeft=true; this.p.wentRight=false;
					this.play("runLeft");
					}
				// Si acaba de correr hacia la derecha
				else if (this.p.vx===0 && this.p.wentRight) 
					this.play("standRight");
				// Si acaba de correr hacia la izquierda
				else if (this.p.vx===0 && this.p.wentLeft) 
					this.play("standLeft");
				}	
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// PowerUp
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("PowerUp", 
		{
		init: function(p) 
			{
			this._super(p,
				{
				posX: 0,
				posY: 0
				});
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Mushroom
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Mushroom", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				asset: "mushroom.png",
				type: Q.SPRITE_POWERUP,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_PLAYER
				});
			this.p.born=false;  // Indica si la 'Mushroom' ha salido de la caja
			this.p.placed=false;  // Indica si la 'Mushroom' ha salido del todo
			this.p.timeSinceBorn=0;  // Indica el tiempo desde que nace
			this.p.moving=false;  // Indica si la 'Mushroom' se está moviendo
			this.p.wentRight=true;  // Indica de donde venía para saber hacia donde tiene que rebotar
			// Componentes
			this.add('tween');  // Al principio sólo nos interesa que la 'Mushroom' salga hacia arriba
			// Eventos
			this.on("hit.sprite",function(collision)
				{
				if (collision.obj.isA("Mario"))
					{
					console.log("Mario coge Mushroom"); 
					this.destroy();
					player.trigger("marioGrows");
					}
				});
			this.on("bump.left, bump.right",function(collision) 
				{
				if (this.p.wentRight)
					{
					this.p.vx=-100;
					this.p.wentRight=false;
					}
				else
					{
					this.p.vx=100;
					this.p.wentRight=true;
					}
				});
			this.on("surpriseBox",function()
				{
				this.p.born=true;
				this.animate({ y: this.p.y-33 }, 0.5);
				});
			},

		step: function(dt)
			{
			if (this.p.born && !this.p.placed)
				this.p.timeSinceBorn=this.p.timeSinceBorn+dt;			
			if (this.p.timeSinceBorn>0.5 && !this.p.placed)
				{
				console.log("Mushroom sale del todo");
				this.p.placed=true; 
				this.add('2d');  // Una vez ha salido la 'Mushroom' tiene colisiones y rebota
				}
			else if (this.p.placed && !this.p.moving)
				{
				console.log("Mushroom se empieza a mover"); 
				this.p.moving=true;
				this.p.vx=100;
				}
			else if (this.p.moving)
				{
				console.log("Mushroom se mueve a "+this.p.vx);
				}
			if (this.p.y>1000)
				{
				console.log("Mushroom cae por precipicio"); 
				this.destroy();
				}
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Flower
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Flower", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				asset: "flower.png",
				type: Q.SPRITE_POWERUP,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_PLAYER
				});
			this.p.born=false;  // Indica si la 'Flower' ha salido de la caja
			this.p.placed=false;  // Indica si la 'Flower' ha salido del todo
			this.p.timeSinceBorn=0;  // Indica el tiempo desde que nace
			// Componentes
			this.add('tween');  // Al principio sólo nos interesa que la 'Flower' salga hacia arriba
			// Eventos
			this.on("hit.sprite",function(collision)
				{
				if (collision.obj.isA("Mario"))
					{
					console.log("Mario coge Flower"); 
					this.destroy();
					player.trigger("marioSuitsUp");
					}
				});
			this.on("surpriseBox",function()
				{
				this.p.born=true;
				this.animate({ y: this.p.y-33 }, 0.5);
				});
			},

		step: function(dt)
			{
			if (this.p.born && !this.p.placed)
				this.p.timeSinceBorn=this.p.timeSinceBorn+dt;			
			if (this.p.timeSinceBorn>0.5 && !this.p.placed)
				{
				this.p.placed=true;
				console.log("Flower sale del todo"); 
				this.add('2d');  // Una vez ha salido la 'Flower' tiene colisiones y peso
				}
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Princess
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Princess", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				asset: "princess.png",
				sensor: true
				});
			// Componentes
			this.add('2d, tween');
			// Eventos
			this.on("sensor",function()
				{
				this.p.sensor=false;
				coins=Q.state.get("coins");
				powerups=Q.state.get("powerups");
				enemies=Q.state.get("enemies");
				if ((coins==30) && (powerups==2) && (enemies==10))
					{
					Q.stageScene("endGame",1, { label: "¡Te quiero Mario!" });
					player.trigger("marioWins");
					}
				else
					{
					Q.stageScene("endGame",1, { label: "¡Te quiero Mario!" });
					player.trigger("marioWins");
					}
				});
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Coin
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Coin", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				sheet: "coin",
				frame: 2,
				sensor: true,  // Para que no exista colisión física
				type: Q.SPRITE_COLLECTABLE,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_PLAYER
				});
			this.p.collected=false;  // Indica si la 'Coin' ha sido cogida por 'Mario'
			this.p.timeCollected=0;  // El tiempo que ha pasado desde que 'Mario' ha cogido la 'Coin'
			// Componentes
			this.add('tween');
			// Eventos
			this.on("hit.sprite",function(collision)
				{
				if (collision.obj.isA("Mario") && !this.p.collected)
					this.collect();
				});
			this.on("surpriseBox",function()
				{
				this.collect();
				});
			},

		collect: function()
			{
			this.p.collected=true;
			Q.audio.play('coin.mp3');
			this.p.frame=0;
			Q.state.inc("coins",1);
			console.log("Moneda cogida. Total: "+Q.state.get("coins"));
			Q.stages[1].trigger("coinCollected");
			this.animate({ y: this.p.y-20, angle: 360 }, 0.5);	
			},

		step: function(dt)
			{
			if (this.p.collected)
				this.p.timeCollected=this.p.timeCollected+dt;			
			if (this.p.timeCollected>0.5)
				{
				console.log("Moneda desaparece"); 
				this.destroy();
				}
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Goomba
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Goomba", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				sheet: "goomba",
				sprite: "goomba",
				vx: 75,
				type: Q.SPRITE_ENEMY,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_PLAYER | Q.SPRITE_ENEMY
				});
			// Componentes
			this.add('2d, aiBounce, animation');
			// Eventos
			this.on("bump.left, bump.right",function(collision) 
				{
				if(collision.obj.isA("Mario")) 
					{
					console.log("Goomba mata a Mario");
					this.p.vx=(-1)*this.p.vx;  // Si un goomba te mata no rebota (así anulamos su aiBounce)
					Q.audio.stop(collision.obj.p.currentSong);
					collision.obj.p.currentSong=collision.obj.p.deathSong;
					Q.audio.play(collision.obj.p.currentSong);
					collision.obj.destroy();
					Q.stageScene("endGame",1, { label: "Te mató un Goomba" }); 
					}
				else if (collision.obj.isA("Goomba"))
					{
					console.log("Goomba choca con Goomba");
					}
				});
			this.on("bump.top",function(collision) 
				{
				if(collision.obj.isA("Mario")) 
					{
					Q.state.inc("enemies",1);
					Q.stages[1].trigger("enemyKilled");
					console.log("Mario mata a Goomba");
					Q.audio.play('squish_enemy.mp3');
					collision.obj.p.vy=-400;
					this.p.vx=0;
					this.play("death",1);  // tiene más prioridad que el 'this.play("run");'
					}
				});
			this.on("destroyGoomba",function()
				{
				this.destroy();
				});			
			},

		step: function(dt)
			{
			if (this.p.vx!=0)
				this.play("run");
			if (this.p.y>1000)
				{
				console.log("Goomba cae por precipicio"); 
				this.destroy();
				}
			}
		});
	
	//////////////////////////////////////////////////////////////////////////
	// Bloopa
	//////////////////////////////////////////////////////////////////////////
	Q.Sprite.extend("Bloopa", 
		{
		init: function(p) 
			{
			// Atributos
			this._super(p,
				{
				sheet: "bloopa",
				sprite: "bloopa",
				type: Q.SPRITE_ENEMY,
				collisionMask: Q.SPRITE_DEFAULT | Q.SPRITE_PLAYER | Q.SPRITE_ENEMY
				});
			this.p.onGround=false;
			this.p.timeOnGround=0;
			// Componentes
			this.add('2d, animation');
			// Eventos
			this.on("bump.left, bump.right",function(collision) 
				{
				if (collision.obj.isA("Mario")) 
					{
					console.log("Bloopa mata a Mario chocando por el lado");
					Q.audio.stop(collision.obj.p.currentSong);
					collision.obj.p.currentSong=collision.obj.p.deathSong;
					Q.audio.play(collision.obj.p.currentSong);
					collision.obj.destroy();
					Q.stageScene("endGame",1, { label: "Te mató un Bloopa" });
					}
				else if (collision.obj.isA("Goomba"))
					{
					console.log("Bloopa choca con Goomba por el lado");
					}
				});
			this.on("bump.bottom",function(collision) 
				{
				this.p.onGround=true;
				if (collision.obj.isA("Mario"))
					{
					console.log("Bloopa mata a Mario chocando por debajo"); 
					Q.audio.stop(collision.obj.p.currentSong);
					collision.obj.p.currentSong=collision.obj.p.deathSong;
					Q.audio.play(collision.obj.p.currentSong);
					collision.obj.destroy();
					Q.stageScene("endGame",1, { label: "Te mató un Bloopa" });
					}
				else if (collision.obj.isA("Goomba"))
					{
					console.log("Bloopa choca con Goomba por debajo");
					}
				});
			this.on("bump.top",function(collision)
				{
				if(collision.obj.isA("Mario")) 
					{
					Q.state.inc("enemies",1);
					Q.stages[1].trigger("enemyKilled");
					console.log("Mario mata a Bloopa");
					Q.audio.play('squish_enemy.mp3');
					collision.obj.p.vy=-400;
					this.p.vy=0;
					this.play("death",1);  // tiene más prioridad que el resto de 'this.play("jump");' y 'this.play("idle");'
					}
				});
			this.on("destroyBloopa",function()
				{
				this.destroy();
				});	
			},

		step: function(dt)
			{
			if (this.p.onGround)
				{
				this.p.timeOnGround=this.p.timeOnGround+dt;
				this.play("idle");
				if (this.p.timeOnGround>0.6)
					{
					this.p.timeOnGround=0;	
					this.p.vy=-600;
					this.p.onGround=false;
					}
				}
			else
				{
				this.play("jump");
				}
			}
		});

	//////////////////////////////////////////////////////////////////////////
	// Componente 'defaultEnemy'
	//////////////////////////////////////////////////////////////////////////
	Q.component("defaultEnemy", 
		{
		// -En 'added:' ponemos todas las cosas que se crean al añadir el componente
		// al Sprite que queramos que en este caso es 'this.entity'. Desde ahí podemos
		// acceder a suspropiedades y métodos
		added: function() 
			{
			// Start the ammo out 1/2 filled
			this.entity.p.ammo = 30;
			},

		// -Para acceder a las funciones desde el Sprite tenemos que hacer
		// 'nombreSprite.nombreComponente.nombreFuncion'. Un ejemplo sería 
		// 'goomba.defaultEnemy.colisionConMario()'
		// -Desde aquí accedemos a las cosas con 'this.entity.'
		colisionConMario: function() 
			{
			
			},

		extend: 
			{
			fire: function() 
				{
				// We can use this.p to set properties
				// because fire is called directly on the player
				if(this.p.ammo > 0) 
					{
					this.p.ammo-=1;
					console.log("Fire!");
					}
				}      
			}	
		});

	//////////////////////////////////////////////////////////////////////////
	// Escena 'startGame'
	//////////////////////////////////////////////////////////////////////////
	Q.scene('startGame',function(stage) 
		{		
		// Iniciar el GameState
		Q.state.init({coins:0,enemies:0,powerups:0});
		// Parar todo el audio
		Q.audio.stop();
		// Elementos del menú principal
		var container = stage.insert(new Q.UI.Container({x: Q.width/2, y: Q.height/2}));
		var button = container.insert(new Q.UI.Button({ x: 0, y: 0, asset: "mainTitleB.png"}));        
		// Me suscribo a los eventos del botón para cuando se haga click
		button.on("click",function()
			{
			Q.clearStages();
			Q.stageScene('level1');
			Q.stageScene("hud",1);	
			});
		// Me suscribo a los eventos de entrada para cuando se presione 'fire'
		Q.input.on("fire",function()
			{
			Q.clearStages();
			Q.stageScene('level1');
			Q.stageScene("hud",1);	
			});
		// Expand the container to visibily fit it's contents
		// (with a padding of 20 pixels)
		container.fit(20);
		});

	//////////////////////////////////////////////////////////////////////////
	// Escena 'endGame'
	//////////////////////////////////////////////////////////////////////////
	Q.scene('endGame',function(stage) 
		{
		var container = stage.insert(new Q.UI.Container({x: Q.width/2, y: Q.height/2, fill: "rgba(0,0,0,0.5)"}));
		var button = container.insert(new Q.UI.Button({ x: 0, y: 0, fill: "#CCCCCC",label: "Jugar de nuevo" }));        
		var label = container.insert(new Q.UI.Text({x:10, y: -10 - button.p.h, label: stage.options.label }));
		// When the button is clicked, clear all the stages
		// and restart the game.
		button.on("click",function()
			{
			Q.clearStages();
			Q.stageScene('startGame');
			});
		// Me suscribo a los eventos de entrada para cuando se presione 'fire'
		Q.input.on("fire",function()
			{
			Q.clearStages();
			Q.stageScene('startGame');
			});
		// Expand the container to visibily fit it's contents
		// (with a padding of 20 pixels)
		container.fit(20);
		});

	//////////////////////////////////////////////////////////////////////////
	// Escena 'hud'
	//////////////////////////////////////////////////////////////////////////
	Q.scene('hud',function(stage) 	
		{
		var container = stage.insert(new Q.UI.Container({ x: 50, y: 0 }));  // El contenedor empieza en x=50,y=0
		this.score = container.insert(new Q.UI.Text({x:110, y: 0, label: "coin-"+Q.state.get("coins")+" ene-"+Q.state.get("enemies")+" pUP-"+Q.state.get("powerups"), color: "white" }));
		stage.on("coinCollected",function()
			{
			this.scene.score.p.label="coin-"+Q.state.get("coins")+" ene-"+Q.state.get("enemies")+" pUP-"+Q.state.get("powerups");
			});
		stage.on("enemyKilled",function()
			{
			this.scene.score.p.label="coin-"+Q.state.get("coins")+" ene-"+Q.state.get("enemies")+" pUP-"+Q.state.get("powerups");
			});
		stage.on("powerUpCollected",function()
			{
			this.scene.score.p.label="coin-"+Q.state.get("coins")+" ene-"+Q.state.get("enemies")+" pUP-"+Q.state.get("powerups");
			});
		container.fit(20);
		});

	//////////////////////////////////////////////////////////////////////////
	// Escena 'level1'
	//////////////////////////////////////////////////////////////////////////
	Q.scene("level1",function(stage) 
		{
		// Efecto parallax de 3 capas
		stage.insert(new Q.Repeater({ asset: "bg_clouds.png", speedX: 0.25, type: 0 }));
		stage.insert(new Q.Repeater({ asset: "bg_mist.png", speedX: 0.5, type: 0 }));
		stage.insert(new Q.Repeater({ asset: "bg_mountains.png", speedX: 0.75, type: 0 }));
		// Desuscribirse de eventos (por si es un restart o un respawn)
		Q.input.off("fire");
		// Creación del nivel
		Q.stageTMX("level.tmx",stage);
		// Creación de Mario
		// Creación de los Enemigos
/**************************************************************************************************************************/		
		///////////////////////////////////////////////////////////
		//// TEST: Dos Goombas chocando ///////////////////////////
		/*player = stage.insert(new Q.Mario({x:150,y:380}));
		stage.insert(new Q.Goomba({x:200,y:380,vx:75}));
		stage.insert(new Q.Goomba({x:350,y:380,vx:-75}));*/
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//// TEST: Fila de goombas (1 a n) ////////////////////////
		/*player = stage.insert(new Q.Mario({x:950,y:380}));
		goombas = new Array;
		for	(i = 0; i < 4; i++) 
			{
			goombas[i] = stage.insert(new Q.Goomba({x:(1000+i*40),y:380}));
			}*/
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//// TEST: Bloopa saltando
		/*player = stage.insert(new Q.Mario({x:150,y:380}));
		stage.insert(new Q.Bloopa({x:350,y:380}));*/
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//// TEST: Princess esperando
		/*player = stage.insert(new Q.Mario({x:150,y:380}));
		stage.insert(new Q.Princess({x:350,y:380}));*/
		///////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////
		//// TEST: Coins
		//***************************************************************//
		// ¿¿¿DE QUE FORMA MUESTRO A MARIO POR DELANTE DE LAS MONEDAS??? //
		//***************************************************************//
		// Si pinto a mario el último sale el último, pero deberia funcionar
		// poniendole un valor p.z mayor que el p.z de las monedas, y no es así
		/*coins = new Array;
		for	(i = 0; i < 10; i++) 
			{
			coins[i] = stage.insert(new Q.Coin({x:(200+i*25),y:450}));
			coins[i+10] = stage.insert(new Q.Coin({x:(200+i*25),y:500}));
			}	
		player = stage.insert(new Q.Mario({x:150,y:380}));*/
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//// TEST: Goombas, bloopa y princess
		/*player = stage.insert(new Q.Mario({x:150,y:380}));
		stage.insert(new Q.Bloopa({x:350,y:380}));
		stage.insert(new Q.Goomba({x:500,y:380,vx:-75}));
		goombas = new Array;
		for	(i = 0; i < 4; i++) 
			{
			goombas[i] = stage.insert(new Q.Goomba({x:(650+i*40),y:380,vx:-75}));
			}
		stage.insert(new Q.Princess({x:250,y:380}));*/
		///////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////
		//// TEST: Coins, goombas y bloopa
		/*coins = new Array;
		for	(i = 0; i < 10; i++) 
			{
			coins[i] = stage.insert(new Q.Coin({x:(200+i*25),y:450}));
			coins[i+10] = stage.insert(new Q.Coin({x:(200+i*25),y:500}));
			}	
		stage.insert(new Q.Bloopa({x:350,y:380}));
		stage.insert(new Q.Goomba({x:500,y:380,vx:-75}));
		goombas = new Array;
		for	(i = 0; i < 4; i++) 
			{
			goombas[i] = stage.insert(new Q.Goomba({x:(650+i*40),y:380,vx:-75}));
			}
		player=stage.insert(new Q.Mario({x:150,y:380}));*/
/**************************************************************************************************************************/
		// Creación de bloopas
		stage.insert(new Q.Bloopa({x:628,y:200}));
		stage.insert(new Q.Bloopa({x:832,y:150}));
		stage.insert(new Q.Bloopa({x:1718,y:150}));
		stage.insert(new Q.Bloopa({x:1785,y:250}));
		stage.insert(new Q.Bloopa({x:1820,y:150}));
		// Creación de goombas
		goombas = new Array;
		for	(i = 0; i < 5; i++) 
			{
			goombas[i] = stage.insert(new Q.Goomba({x:(1115+i*40),y:380,vx:-75}));
			}
		// Creación de monedas
		coins = new Array;
		for	(i = 0; i < 10; i++) 
			{
			if (i<=1)
				{
				stage.insert(new Q.Coin({x:(1115+i*25),y:35}));  // Las dos difíciles de arriba
				}
			coins[i] = stage.insert(new Q.Coin({x:(55+i*25),y:235}));  // Entre las cajas
			coins[i+10] = stage.insert(new Q.Coin({x:(1015+i*25),y:235}));  // A mitad del juego
			}
		// Creación de 'Mario'	
		player=stage.insert(new Q.Mario({x:90,y:500}));
		// Creación de 'Princess'
		stage.insert(new Q.Princess({x:2000,y:100}))
		// Creación y gestión de powerUps
		powerUps = new Array;
		powerUps[0] = stage.insert(new Q.PowerUp({posX:6,posY:13}));
		powerUps[1] = stage.insert(new Q.PowerUp({posX:23,posY:13}));
		stage.on("checkPowerUp",function(pos)  // Evento que se llama cuando Mario abre una caja '?' para comprobar si hay 'PowerUp'
			{
			for	(i = 0; i < powerUps.length; i++) 
				{
				powerUpX=powerUps[i].p.posX;
				powerUpY=powerUps[i].p.posY;
				if (powerUpX==pos.posTileX && powerUpY==pos.posTileY)
					{
					console.log("Hay powerup en ("+pos.posTileX+","+pos.posTileY+")");
					player.trigger("powerUpDiscovered");
					break;
					}
				}
			});
		// Creación y gestión de la cámara
		stage.add("viewport");  // Añade componente viewport (y sus métodos a la escena)
		stage.centerOn(150,370); 
		stage.viewport.offsetY = 160; stage.viewport.offsetX = -80;  // Crea un offset del viewport para que no siga a Mario centrado
		stage.follow(player,{x: true, y:false});  // Usamos el método follow del viewport (añadido a la escena) para seguir a Mario (sólo en el eje x)
		stage.on("cameraFocus",function(toLeft)
			{
			if (toLeft)  // Si miramos hacia la izquierda...
				{
				if (stage.viewport.offsetX<80)  // ...y no llegamos a 100 tenemos que seguir sumando para mover la cámara
					stage.viewport.offsetX+=10;
				}
			else  // Si miramos hacia la derecha...
				{
				if (stage.viewport.offsetX>-80)  // ...y no llegamos a -100 tenemos que seguir restando para mover la cámra
					stage.viewport.offsetX-=10;
				}
			});
		});

	Q.loadTMX("level.tmx, grow.png, mario_fire.png, mario_fire.json, mario_large.png, mario_large.json, mario_small.png, mario_small.json, goomba.png, goomba.json, bloopa.png, bloopa.json, coin.png, coin.json, princess.png, mushroom.png, flower.png, mainTitleB.png, bg_clouds.png, bg_mist.png, bg_mountains.png, coin.mp3, squish_enemy.mp3, jump_small.mp3, music_die.mp3, music_level_complete.mp3, music_main.mp3",function() 
		{
		Q.compileSheets("mario_small.png","mario_small.json");
		Q.compileSheets("mario_large.png","mario_large.json");
		Q.compileSheets("mario_fire.png","mario_fire.json");
	    Q.compileSheets("goomba.png","goomba.json");
	    Q.compileSheets("bloopa.png","bloopa.json");
		Q.compileSheets("coin.png","coin.json");
		Q.animations("marioSmallR", 
			{
			runRight: { frames: [0,1,2,3], rate: 1/15}, 
			runLeft: { frames: [14,15,16,17], rate: 1/15 },
			standRight: { frames: [0], loop: false },
			standLeft: { frames: [14], loop: false },
			jumpRight: { frames: [4], loop: false },
			jumpLeft: { frames: [18], loop: false }
			});
		Q.animations("marioLargeR", 
			{
			runRight: { frames: [0,1,2,3], rate: 1/15}, 
			runLeft: { frames: [14,15,16,17], rate: 1/15 },
			standRight: { frames: [0], loop: false },
			standLeft: { frames: [14], loop: false },
			jumpRight: { frames: [4], loop: false },
			jumpLeft: { frames: [18], loop: false }
			});
		Q.animations("marioFireR", 
			{
			runRight: { frames: [0,1,2,3], rate: 1/15}, 
			runLeft: { frames: [14,15,16,17], rate: 1/15 },
			standRight: { frames: [0], loop: false },
			standLeft: { frames: [14], loop: false },
			jumpRight: { frames: [4], loop: false },
			jumpLeft: { frames: [18], loop: false }
			});
		Q.animations("goomba",
			{
			run: { frames: [0,1], rate: 1/2 },
			death: { frames: [2], rate: 1/2, loop: false, trigger: "destroyGoomba" }
			});
		Q.animations("bloopa", 
			{
			jump: { frames: [0], loop: false }, 
			idle: { frames: [1], loop: false },
			death: { frames: [2], rate: 1/2, loop: false, trigger: "destroyBloopa" }
			});
		Q.stageScene("startGame");
		});
	});	