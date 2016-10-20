/**
 * MemoryGame es la clase que representa nuestro juego. Contiene un array con la cartas del juego,
 * el número de cartas encontradas (para saber cuándo hemos terminado el juego) y un texto con el mensaje
 * que indica en qué estado se encuentra el juego
 */
var MemoryGame = MemoryGame || {};

/**
 * Constructora de MemoryGame
 */
MemoryGame=function(gs) 
	{
	var	gs;	 // graphic server
	var	arrayOrigin;  // array de 16 posiciones de las cartas originales para distribuirlas en arrayCartas
	var	arrayCards;  // array de 16 posiciones con los nombres de las cartas del juego actual
	var isInTimeout;  // nos indica si estamos en el tiempo que están dos cartas boca arriba comparándose
	var isFirstCard;  // nos indica si estamos en el tiempo en que está la primera carta boca arriba
	var previousCard;  // cuando estamos con la segunda carta boca arriba guardamos aquí la primera para poder comparar
	var actualMessage;  // muestra el mensaje actual
	var totalMatches;  // indica el total de matches. Cuando son 8 hemos ganado
 	this.gs=gs;
 	this.arrayOrigin=["8-ball","potato","dinosaur","kronos","rocket","unicorn","guy","zeppelin",
					  "8-ball","potato","dinosaur","kronos","rocket","unicorn","guy","zeppelin"];
 	this.arrayCards=new Array(16);
	this.isInTimeout=false;
	this.isFirstCard=true;
	this.actualMessage="Memory Game";
	this.totalMatches=0;
	};

MemoryGame.prototype=
	{
	initGame: function() 
		{
		/**
		 * Inicializa el juego creando las cartas (2 de cada tipo), desordenándolas
		 * y dando comienzo al bucle del juego
		 */
		var cardName;
		for (var i = 0; i < 16; i++) 
			{ 
		    cardName = this.getRandomCard();  // Obtiene una carta del montón 'arrayOrigin' aleatoriamente...
		    this.arrayCards[i] = new MemoryGame.Card(cardName);  // ...y crea una carta guardandola en el 'arrayCards'
			console.log("Carta "+i+" creada: "+this.arrayCards[i].id);
			}
		this.loop();  // Ejecutamos el bucle del juego
		},
	loop: function() 
		{
		/**
		 * Bucle del juego que se repite cada 16ms (60fps). En nuestro caso
		 * nuestro bucle sólo se ocupa de llamar a 'draw'
		 */
		//setInterval(this.draw,16);
		var self=this;
		setInterval(function(){self.draw();},16);
		},
	draw: function() 
		{
		/*
		var self;
		self=this.game;
		for (var i = 0; i < 16; i++)  // Dibuja todas las cartas de arrayCards (según su flip) 
			{ 
			self.arrayCards[i].draw(self.gs,i);  // Dibuja la carta de la posición i
			}
		*/
		for (var i = 0; i < 16; i++) 
			{ 
			this.arrayCards[i].draw(this.gs,i);
			}
		},
	onClick: function(cardId)
		{
		/**
		 * Se llama cada vez que un jugador pulsa en una carta. Da la vuelta a la carta
		 * y si son la misma las deja boca arriba y si no les da la vuelta de nuevo al poco
		 */
		if (!this.isInTimeout)  // Para recoger eventos de click tenemos que tener 'isInTimeOut' a false
			{
			if (this.isFirstCard)  // Si hemos hecho click en la primera carta...
				{
				if (!this.arrayCards[cardId].flipValue)  // ...y la carta no está volteada
					{
					console.log("--------------------------------------------");
					console.log("Carta A (pos: "+cardId+", nombre: "+this.arrayCards[cardId].id+")");
					this.arrayCards[cardId].flip();  // ...marcamos la carta como volteada,...
					this.previousCard=this.arrayCards[cardId];  // ...guardamos el nombre de la carta para compararla luego y...
					this.isFirstCard=false;  // ...evidentemente 'isFirstCard' se pone a false
					}
				}
			else if (!this.isFirstCard)  // Si hemos hecho click en la segunda carta... 
				{
				if (!this.arrayCards[cardId].flipValue)  // ...y la carta no está volteada
					{					
					console.log("Carta B (pos: "+cardId+", nombre: "+this.arrayCards[cardId].id+")");
					this.arrayCards[cardId].flip();  // ...marcamos la carta como volteada,...
					this.arrayCards[cardId].draw(this.gs,cardId);  // ...dibujamos la carta,...
					this.isInTimeout=true;  // ...establecemos 'isTimeOut' a true por tener dos cartas levantadas...
					self=this;
					setTimeout(function()	{
											self.arrayCards[cardId].compareTo(self.previousCard);  // Comparamos con la carta previa...
											self.isInTimeout = false;  // ...y una vez transcurrido el timeout, descativamos la guarda
											}
											
											,500);
					this.isFirstCard=true;  // ...y en concreto en la primera
					}
				}
			}
		},
	/*
	timeoutTasks: function()
		{
		this.arrayCards[this.cardId].compareTo(this.previousCard);  // Durante el timeout comparamos las cartas y decidimos que hacer con ellas
		},
	*/
	getRandomCard: function ()
		{ 
		/**
		 * Función auxiliar que nos escoge aleatoriamente una carta de las que hay en 'num'.
		 * La elimina con splice y devuelve su nombre en 'cardName'
		 */
		var index;
		var cardName;
		index = Math.floor(Math.random()*this.arrayOrigin.length);
		cardName = this.arrayOrigin[index];
		this.arrayOrigin.splice(index, 1);
		return cardName;
		}
	}

/**
 * Constructora de las cartas del juego. Recibe como parámetro el nombre del sprite que representa la carta.
 * Dos cartas serán iguales si tienen el mismo sprite.
 * La carta puede guardar la posición que ocupa dentro del tablero para luego poder dibujarse
 * @param {string} id Nombre del sprite que representa la carta
 */
MemoryGame.Card = function(id) 
	{
	var id;
	var flipValue;
	var actualMessage;
	this.id=id;  // El nombre de la carta
	this.flipValue = false;  // Las cartas empiezan dadas la vuelta
	//this.actualMessage = "Memory Game";  // El mensaje empieza siendo "Memory Game"
	};

MemoryGame.Card.prototype=
	{
	flip: function() 
		{
		if(!this.flipValue)
			{
			this.flipValue = true;
			}
		else
			{
			this.flipValue = false;
			}

		},
	compareTo: function(otherCard)
		{
		if (this.id===otherCard.id)  // Si son las mismas deja un mensaje indicándolo
			{
			if (game.totalMatches===7)
				{
				console.log("GANASTE :D");
				console.log("--------------------------------------------");
				game.actualMessage = "You win";
				game.totalMatches++;
				}
			else
				{
				console.log("ACIERTO :)");
				game.actualMessage = "Match Found";
				game.totalMatches++;
				}
			}
		else  // Si no son las mismas cartas las vuelve a ocultar y lo indica
			{
			console.log("FALLO :(");
			game.actualMessage = "Try again";
			this.flip();
			otherCard.flip();
			}
		},
	draw: function(gs, pos)
		{
		if (this.flipValue)  // Si esta volteada se muestra su imagen
			{
			gs.draw(this.id,pos);  // ("nombre",posición)
			}
		else  // Si no está volteada se muestra la parte trasera
			{
			gs.draw("back",pos);
			}
		gs.drawMessage(game.actualMessage);
		}
	}

