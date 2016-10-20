var sprites = 
  {
  frog: { sx: 0, sy: 0, w: 48, h: 48, frames: 1 },
  bg: { sx: 433, sy: 0, w: 320, h: 480, frames: 1 },
  car1: { sx: 143, sy: 0, w: 48, h: 48, frames: 1 },
  car2: { sx: 191, sy: 0, w: 48, h: 48, frames: 1 },  
  car3: { sx: 239, sy: 0, w: 96, h: 48, frames: 1 },
  car4: { sx: 335, sy: 0, w: 48, h: 48, frames: 1 },
  car5: { sx: 383, sy: 0, w: 48, h: 48, frames: 1 },
  log: { sx: 287, sy: 383, w: 144, h: 48, frames: 1 },
  death: { sx: 0, sy: 143, w: 48, h: 48, frames: 4 }
  };

var enemies = 
  {
  car1: { x: 48*7,   y: 48*5, sprite: 'car1', speed: 90, direction: -1 },
  car2: { x: 48*7,   y: 48*6, sprite: 'car2', speed: 110, direction: -1 },
  car4: { x: 48*7,   y: 48*8, sprite: 'car4',  speed: 60, direction: -1 },
  car5: { x: 48*-1,   y: 48*7, sprite: 'car5', speed: 70, direction:  1 },
  log: { x: 0,   y: 0, sprite: 'log', speed: 70, direction:  1 }
  };

var OBJECT_PLAYER = 1,
    OBJECT_CAR = 2,
    OBJECT_ENEMY_PROJECTILE = 8,
    GAME_BACKGROUND = 16;
    OBJECT_WATER = 32;
    OBJECT_HOME = 64;

var level1 = 
  [
    // Start,   End, Gap,  Type,   Override
    [ 100,  20000, 1500, 'car1' ],
    [ 100,  20000, 2000, 'car2' ],
    [ 100,  20000, 2750, 'car4' ],
    [ 100,  20000, 3000, 'car5' ],
  ];

var treeLevel = 
  [
    // Start,   End, Gap,  Type,   Override
    [ 100,  20000, 3200, 'log' , { x: 48*7,  y: 48*1, speed: 90, direction: -1 }],
    [ 100,  20000, 4500, 'log' , { x: 48*-3,  y: 48*2, speed: 70, direction: 1 }],
    [ 100,  20000, 3500, 'log' , { x: 48* 7, y: 48*3, speed: 60, direction: -1}]
  ];

var startGame = function() 
  {
  // La capa 0 es el fondo
  Game.setBoard(0,new Background());
  // La capa de título tiene transparencia
  Game.setBoard(1,new TitleScreen("FROGGER","PRESS SPACE TO START JUMPING",playGame));
  };

var playGame = function(board) 
  {
  Game.setBoard(2,null);
  // La capa 1 es el juego
  var board = new GameBoard();
  board.add(new Frog());
  board.add(new Level(level1,Car,winGame));
  board.add(new Water());
  board.add(new Home());
  board.add(new Level(treeLevel,Log,winGame));
  Game.setBoard(1,board);
  };

var winGame = function() 
  {
  Game.setBoard(2,new TitleScreen("You win!","Press space to play again",playGame));
  };

var loseGame = function() 
  {
  Game.setBoard(2,new TitleScreen("You lose!","Press space to play again",playGame));
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Background'
////////////////////////////////////////////////////////////////////////////////////////////////// 
// Constructora de la clase 'Background' 
var Background = function() 
  {
  this.setup('bg', {});  // Hace referencia al método 'setup' heredado de 'Sprite'

  this.x = Game.width/2 - this.w / 2;
  this.y = Game.height - this.h;

  this.step = function(dt) 
    {
    };

  };

// La clase 'Background' hereda de clase 'Sprite'
Background.prototype = new Sprite();

// Atributos propios de la clase 'Background'
Background.prototype.type = GAME_BACKGROUND;

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Frog'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Frog'
var Frog = function() 
  { 
  this.setup('frog', { vx: 0, vy:0, restTime:0.20, jump:48  });  // Hace referencia al método 'setup' heredado de 'Sprite'
  this.vLog = 0;  // Indica la velocidad a la que estamos en el árbol
  this.rest = this.restTime;  // El tiempo que queda hasta que podamos coger tecla
  this.x = Game.width/2 - this.w / 2;  // Posición 'x' inicial de la rana
  this.y = Game.height - this.h;  // Posición 'y' inicial de la rana
  };

// La clase 'Frog' hereda de clase 'Sprite'
Frog.prototype = new Sprite();

// Atributos propios de la clase 'Frog'
Frog.prototype.type = OBJECT_PLAYER;

// Métodos propios de la clase 'Frog'
Frog.prototype.hit = function(damage) 
  {
  if(this.board.remove(this)) 
    {
    this.board.add(new Death(this.x, this.y));
    }
  };

Frog.prototype.onLog = function(speed) 
  {
  this.vLog = speed;
  };

Frog.prototype.deep = function(speed) 
  {
  if((this.vLog)===0 && this.y>=48 && this.y<=144 )
    {
    this.hit();
    }
  };

Frog.prototype.victory = function(speed) 
  {
  if(this.y===0)
    {
    this.board.remove(this);
    winGame();
    }
  };

Frog.prototype.step = function(dt) 
  {
  // La función 'step' se llama en cada ciclo del juego y sólo si hemos presionado la tecla correcta y ha pasado
  // el tiempo correspondiente a 'restTime' se hace caso a la pulsación de la tecla
  if(Game.keys['left'] && this.rest < 0) 
    { 
    this.rest = this.restTime;  // se actualiza el tiempo de timeOut hasta la siguiente pulsación 
    this.vx = -this.jump;  // 'vx' guarda 48 píxeles menos
    }
  else if(Game.keys['right'] && this.rest < 0) 
    { 
    this.rest = this.restTime;  // se actualiza el tiempo de timeOut hasta la siguiente pulsación
    this.vx = this.jump;  //'vx' guarda 48 píxeles más
    }
  else if(Game.keys['up'] && this.rest < 0) 
    {
    this.rest = this.restTime;  // se actualiza el tiempo de timeOut hasta la siguiente pulsación
    this.vy = -this.jump;  // 'vy' guarda 48 píxeles menos
    }
  else if(Game.keys['down'] && this.rest < 0) 
    { 
    this.rest = this.restTime;  // se actualiza el tiempo de timeOut hasta la siguiente pulsación
    this.vy = this.jump;  // 'vy' guarda 48 píxeles más
    }
  else  // si no se pulsa ninguna tecla 'vx' y 'vy' no guardan ningún aumento
    { 
    this.vx = 0; 
    this.vy = 0; 
    }

  this.x += this.vx + this.vLog*dt;  // La posición de la rana en x depende de hacia donde la movemos y si está en el árbol
  this.y += this.vy;  // La posición de la rana en y depende de hacia donde la movemos

  if(this.x < 0)  // La rana nunca se puede salir por la izquierda
    { 
    this.x = 0; 
    }
  else if(this.x > Game.width - this.w)  // La rana nunca se puede salir por la derecha
    { 
    this.x = Game.width - this.w;
    }

  if(this.y < 0)  // La rana nunca se puede salir por arriba
    { 
    this.y = 0;
    }
  else if(this.y > Game.height - this.h)  // La rana nunca se puede salir por abajo
    { 
    this.y = Game.height - this.h;
    }
    
  this.rest-=dt;  // En cada paso (step) restamos 'dt' del tiempo 'rest' para poder coger pulsaciones de tecla
  this.vLog = 0;  // Como al final de cada paso no sabemos si salimos del árbol ponemos a 0 'vLog'
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Car'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Car'
var Car = function(blueprint,override) 
  {
  this.merge(this.baseParameters);
  this.setup(blueprint.sprite,blueprint);
  this.merge(override);
  };

// La clase 'Car' hereda de clase 'Sprite'
Car.prototype = new Sprite();

// Atributos propios de la clase 'Car'
Car.prototype.type = OBJECT_CAR;
Car.prototype.baseParameters = { x: 0, y: 0, sprite: 0, speed: 0, direction: 0 };

// Métodos propios de la clase 'Car'
Car.prototype.step = function(dt) 
  {
  // La función 'step' se llama en cada ciclo del juego y calcula la posición del coche dependiendo del
  // tiempo que haya pasado (dt)
  this.t += dt;  // El tiempo que ha pasado desde la última vez que se llamó
  this.vx = this.speed;  // La velocidad a la que se mueve el coche
  this.cdirection = this.direction;  // La dirección en la que se mueve el coche (-1 o 1)

  this.x += this.vx * dt * this.cdirection;  // Se calcula la posición de la rana con s=v*t

  var collision = this.board.collide(this,OBJECT_PLAYER);  
  // Comprueba si hay colisión de coche (this) con jugador (OBJECT_PLAYER), en el caso de que haya coli-
  // sión devuelve a la rana en 'collision', en caso de que no haya devuelve 'false' en 'collision'
  
  if(collision)  // Si hay colisión...
    {
    collision.hit();  // ...llama al método 'hit' de 'Sprite'...
    this.board.remove(this);  // ...y elimina al coche
    }

  this.reload-=dt;

  if(this.x < -Game.width-48 || this.x > Game.width+48)  // Si el coche se sale de la pantalla... 
    {
    this.board.remove(this);  // ...lo elimina
    }
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Log'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Log'
var Log = function(blueprint,override) 
  {
  this.merge(this.baseParameters);
  this.setup(blueprint.sprite,blueprint);
  this.merge(override);
  };

// La clase 'Log' hereda de clase 'Sprite'
Log.prototype = new Sprite();

// Atributos propios de la clase 'Log'
Log.prototype.type = OBJECT_CAR;
Log.prototype.baseParameters = { x: 0,   y: 0, sprite: 0, speed: 0, direction: 0 };

// Métodos propios de la clase 'Log'
Log.prototype.step = function(dt) 
  {
  // La función 'step' se llama en cada ciclo del juego y calcula la posición del tronco dependiendo del
  // tiempo que haya pasado (dt)
  this.t += dt;
  this.vx = this.speed;
  this.cdirection = this.direction;

  this.x += this.vx * dt * this.cdirection;

  var collision = this.board.collide(this,OBJECT_PLAYER);
  // Comprueba si hay colisión de tronco (this) con jugador (OBJECT_PLAYER), en el caso de que haya coli-
  // sión mueve a la rana en con su método 'onLog', en caso de que no haya devuelve 'false' en 'collision'

  if(collision)  // Si hay colisión... 
    {
    collision.onLog(this.speed * this.direction);  // ...llama al método 'onLog' de 'Frog'
    }

  if(this.x < -Game.width-144 || this.x > Game.width+144)  // Si el tronco se sale de la pantalla...  
    {
    this.board.remove(this);  // ...lo elimina
    }
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Water'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Water'
var Water = function() 
  {
  };

// Atributos propios de la clase 'Water'
Water.prototype = new Sprite();
Water.prototype.type = OBJECT_WATER;

// Métodos propios de la clase 'Water'
Water.prototype.step = function(dt) 
  {
  var collision = this.board.collide(this,OBJECT_PLAYER);
  // Comprueba si hay colisión de agua (this) con jugador (OBJECT_PLAYER), en el caso de que haya coli-
  // sión devuelve a la rana en 'collision', en caso de que no haya devuelve 'false' en 'collision'

  if(collision)  // Si hay colisión... 
    {
    collision.deep();  // ...llama al método 'deep' de 'Frog'
    }
  };

Water.prototype.draw = function() 
  {
  // Se reimplenta el método 'draw' para que no dibuje nada (el agua no tiene sprite)
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Death'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Death'
var Death = function(x,y) 
  {
  this.setup('death', { frame: 0 });
  this.x = x;
  this.y = y;
  this.next = 0;  // Acumula tiempo para indicarnos cuando pintar el siguiente frame
  };

// Atributos propios de la clase 'Death'
Death.prototype = new Sprite();

// Métodos propios de la clase 'Death'
Death.prototype.step = function(dt) 
  {
  if(this.next>0.16)  // Si han pasado 0.16s desde la colisión (o el anterior frame)...
    {
    this.frame++;  // ...pasamos al siguiente frame
    if(this.frame >= 4)  // Si se ha recorrido toda la animación... 
      {
      this.board.remove(this);  // ...eliminamos la animación y...
      loseGame();  // ...acabamos el juego perdiendo
      }
    this.next = 0;
    }

  this.next = this.next + dt;  // Aumentamos 'next' en 'dt'
  };

//////////////////////////////////////////////////////////////////////////////////////////////////
// Clase 'Home'
//////////////////////////////////////////////////////////////////////////////////////////////////  
// Constructora de la clase 'Home'
var Home = function() 
  { 
  this.step = function(dt) 
    {
    var collision = this.board.collide(this,OBJECT_PLAYER);
    if(collision) 
      {
      collision.victory();
      }
    };
  };

// Atributos propios de la clase 'Home'
Home.prototype = new Sprite();
Home.prototype.type = OBJECT_HOME;

// Métodos propios de la clase 'Home'
Home.prototype.draw = function() 
  {
  };

/*
Aquí comienza la ejecución. Cuando se carga la ventana (evento 'load') se llama a la función
'Game.initialize("game",sprites,startGame)'. 
*/
window.addEventListener("load", function() 
  {
  Game.initialize("game",sprites,startGame); 
  });