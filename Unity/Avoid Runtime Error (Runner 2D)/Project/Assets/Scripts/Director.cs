using UnityEngine;
/*
 * Director.cs
 * -----------
 * -Script asociado a Main Camera. Lo hemos llamado 'Director.cs' para resumir que esta cámara 
 * funciona como si tuviese un director de cine detrás que se encarga de muchas cosas.
 * -El director controla el movimiento de la cámara durante el uso del menú (los créditos de una
 * película), durante las transiciones (las esenas guionizadas) y durante el juego propiamente 
 * dicho (las escenas de acción que siguen al actor por donde va).
 * -El director no se puede encargar de todo y tiene que delegar tareas en otros integrantes del
 * equipo: los actores (enemigos) tienen un guión de dónde colocarse y en qué momento salir a 
 * escena (enemySpawner.cs) y los responsables de realización se ocupan de colocar los escenarios 
 * (pasillos y clases) para que se pueda desarrollar la acción (scenarioSpawner.cs). 
 */
public class Director : MonoBehaviour
    {
    // Atributos para gestionar menú
    private bool inMenu = true;  // Indica que estamos en menú
    private Vector3 menuScreenPosition = new Vector3(38.4f, 0f, -10f);  // Posición del menú principal
    private Vector3 menuConfigPosition = new Vector3(38.4f, 10.8f, -10f);  // Posición del menú de configuración
    private Vector3 menuCreditsPosition = new Vector3(38.4f, -10.8f, -10f);  // Posición del menú de créditos
    private GameObject selectCursor;  // La referencia al cursor de selección del menú
    private enum menuItems
        {
        defaultItem,
        graphics, music, sound, backFromConfig,
        mrLuis, mrFer, start, config,
        credits, backFromCredits
        };
    private menuItems highlighted=menuItems.mrLuis;  // Se empieza seleccionando en Mr.Luis
    private menuItems playerChosen=menuItems.defaultItem;  // El elegido no existe hasta que se presiona "Fire1"
    private bool alreadyPressed = false;  // Indica si tenemos una tecla presionada para no volver a coger la pulsación

    // Atributos para gestionar transiciones
    private bool inTransition = false;  // Indica si estamos moviéndonos entre menús o en escena
    private enum transitionItems
        {
        defaultItem,
        startDialogue,
        menuToStart, menuToCredits, menuToConfig,
        creditsToMenu,
        configToMenu
        };
    private transitionItems actualTransition = transitionItems.defaultItem;  // La transición elegida no existe hasta que empezamos

    // Atributos para gestionar el juego
    private bool inGame = false;  // Indica si estamos jugando
    public GameObject player;  // El jugador
    private Transform objetivo;  // El transform del jugador para que lo siga la cámara
    public float offset = 2f;  // Offset de la cámara respecto al jugador
    private bool playerSpawned = false;  // Nos indica si el jugador ya está en escena

    void Start ()
        {
        GetComponent<Transform>().position = menuScreenPosition;
        }

    void Update()
        {
        if (inMenu)
            {
            menuLogic();
            }
        else if (inTransition)
            {
            transitionLogic();
            }
        else if (inGame)
            {
            gameLogic();
            }
        }

    /* Lógica de menú:
     * ---------------
     * Este código gestiona el menú. Cómo se mueve el cursor por él y las acciones que se toman
     * en cada selección. Estas acciones pueden implicar movimientos de cámara.
     */
    void menuLogic()
        {
        if (isPressed() && !alreadyPressed)  // Si se presiona una tecla de menú que aún no lo estaba...
            {
            alreadyPressed = true;
            if (Input.GetAxis("Fire1") > 0)  // Selección
                {
                // OJO: el +38.4f es debido a que la pantalla de menú está desplazada 19.2*2 a la derecha
                switch (highlighted)
                    {
                    ////////////////////
                    // Menú principal //
                    ////////////////////
                    // Pulsamos "Fire1" en "mrLuis"
                    case menuItems.mrLuis:
                        playerChosen = menuItems.mrLuis;
                        // Cambiar los sprites de player y el de selección que aparezca seleccionado
                        toSelection(menuItems.start, -4.8f + 38.4f, -2, 0);
                        break;
                    // Pulsamos "Fire1" en "mrFer"
                    case menuItems.mrFer:
                        playerChosen = menuItems.mrFer;
                        // Cambiar los sprites de player y el de selección que aparezca seleccionado
                        toSelection(menuItems.start, -4.8f + 38.4f, -2, 0);
                        break;
                    // Pulsamos "Fire1" en "start"
                    case menuItems.start:
                        inMenu = false; inGame = false;
                        actualTransition = transitionItems.menuToStart; inTransition = true;
                        alreadyPressed = false;
                        break;
                    // Pulsamos "Fire1" en "config"
                    case menuItems.config:
                        inMenu = false; inGame = false;
                        actualTransition = transitionItems.menuToConfig; inTransition = true;
                        alreadyPressed = false;
                        break;
                    // Pulsamos "Fire1" en "credits"
                    case menuItems.credits:
                        inMenu = false; inGame = false;
                        actualTransition = transitionItems.menuToCredits; inTransition = true;
                        alreadyPressed = false;
                        break;
                    ///////////////////////////
                    // Menú de configuración //
                    ///////////////////////////
                    // Pulsamos "Fire1" en "backFromConfig"
                    case menuItems.backFromConfig:
                        inMenu = false; inGame = false;
                        actualTransition = transitionItems.configToMenu; inTransition = true;
                        alreadyPressed = false;
                        break;
                    //////////////////////
                    // Menú de créditos //
                    //////////////////////
                    // Pulsamos "Fire1" en "backFromCredits"
                    case menuItems.backFromCredits:
                        inMenu = false; inGame = false;
                        actualTransition = transitionItems.creditsToMenu; inTransition = true;
                        alreadyPressed = false;
                        break;
                    /////////////
                    // Default //
                    /////////////
                    // Pulsamos "Fire1" en cualquier otro momento
                    default:
                        Debug.Log("Sin acción para Fire1");
                        break;
                    }
                }
            else if (Input.GetAxis("Vertical") > 0)  // Up
                {
                switch (highlighted)
                    {
                    ////////////////////
                    // Menú principal //
                    ////////////////////
                    // Pulsamos "Up" en "start"
                    case menuItems.start:
                        toSelection(menuItems.mrLuis, -6.75f + 38.4f, 2.2f, 0);
                        break;
                    // Pulsamos "Up" en "config"
                    case menuItems.config:
                        toSelection(menuItems.mrFer, 6.75f + 38.4f, 2.2f, 0);
                        break;
                    // Pulsamos "Up" en "credits"
                    case menuItems.credits:
                        toSelection(menuItems.mrFer, 6.75f + 38.4f, 2.2f, 0);
                        break;
                    ///////////////////////////
                    // Menú de configuración //
                    ///////////////////////////
                    // Pulsamos "Up" en "backFromConfig"
                    case menuItems.backFromConfig:
                        toSelection(menuItems.sound, 31.5f, 8.51f, 0);
                        break;
                    // Pulsamos "Up" en "sound"
                    case menuItems.sound:
                        toSelection(menuItems.music, 31.5f, 10.18f, 0);
                        break;
                    // Pulsamos "Up" en "music"
                    case menuItems.music:
                        toSelection(menuItems.graphics, 31.5f, 11.83f, 0);
                        break;
                    /////////////
                    // Default //
                    /////////////
                    // Pulsamos "Up" en cualquier otro momento
                    default:
                        Debug.Log("Sin acción para Up");
                        break;
                    }
                }
            else if (Input.GetAxis("Vertical") < 0)  // Down
                {
                switch (highlighted)
                    {
                    ///////////////////////////
                    // Menú de configuración //
                    ///////////////////////////
                    // Pulsamos "Down" en "graphics"
                    case menuItems.graphics:
                        toSelection(menuItems.music, 31.5f, 10.18f, 0);
                        break;
                    // Pulsamos "Down" en "music"
                    case menuItems.music:
                        toSelection(menuItems.sound, 31.5f, 8.51f, 0);
                        break;
                    // Pulsamos "Down" en "sounds"
                    case menuItems.sound:
                        toSelection(menuItems.backFromConfig, 31.5f, 7.33f, 0);
                        break;
                    /////////////
                    // Default //
                    /////////////
                    // Pulsamos "Down" en cualquier otro momento
                    default:
                        Debug.Log("Sin acción para Down");
                        break;
                    }
                }   
            else if (Input.GetAxis("Horizontal") > 0)  // Right
                {
                switch (highlighted)
                    {
                    ////////////////////
                    // Menú principal //
                    ////////////////////
                    // Pulsamos "Right" en "mrLuis"
                    case menuItems.mrLuis:
                        toSelection(menuItems.mrFer, 6.75f + 38.4f, 2.2f, 0);
                        break;
                    // Pulsamos "Right" en "start"
                    case menuItems.start:
                        toSelection(menuItems.config, 0 + 38.4f, -2, 0);
                        break;
                    // Pulsamos "Right" en "config"
                    case menuItems.config:
                        toSelection(menuItems.credits, 4.8f + 38.4f, -2, 0);
                        break;
                    /*
                    ///////////////////////////
                    // Menú de configuración //
                    ///////////////////////////
                    // Pulsamos "Right" en "backFromConfig"
                    case menuItems.backFromConfig:
                        toSelection(menuItems.sound, 0, 0, 0);
                        break;
                    // Pulsamos "Right" en "sound"
                    case menuItems.sound:
                        toSelection(menuItems.music, 0, 0, 0);
                        break;
                    // Pulsamos "Right" en "music"
                    case menuItems.music:
                        toSelection(menuItems.graphics, 0, 0, 0);
                        break;
                    */
                    /////////////
                    // Default //
                    /////////////
                    // Pulsamos "Right" en cualquier otro momento
                    default:
                        Debug.Log("Sin acción para Right");
                        break;
                    }
                }
            else if (Input.GetAxis("Horizontal") < 0)  // Left
                {
                switch (highlighted)
                    {
                    ////////////////////
                    // Menú principal //
                    ////////////////////
                    // Pulsamos "Left" en "mrFer"
                    case menuItems.mrFer:
                        toSelection(menuItems.mrLuis, -6.75f + 38.4f, 2.2f, 0);
                        break;
                    // Pulsamos "Left" en "credits"
                    case menuItems.config:
                        toSelection(menuItems.start, -4.8f + 38.4f, -2, 0);
                        break;
                    // Pulsamos "Left" en "credits"
                    case menuItems.credits:
                        toSelection(menuItems.config, 0 + 38.4f, -2, 0);
                        break;
                    /*
                    ///////////////////////////
                    // Menú de configuración //
                    ///////////////////////////
                    // Pulsamos "Left" en "sound"
                    case menuItems.sound:
                        toSelection(menuItems.backFromConfig, 0, 0, 0);
                        break;
                    // Pulsamos "Left" en "music"
                    case menuItems.music:
                        toSelection(menuItems.sound, 0, 0, 0);
                        break;
                    // Pulsamos "Left" en "graphics"
                    case menuItems.graphics:
                        toSelection(menuItems.music, 0, 0, 0);
                        break;
                    */
                    /////////////
                    // Default //
                    /////////////
                    // Pulsamos "Left" en cualquier otro momento
                    default:
                        Debug.Log("Sin acción para Left");
                        break;
                    }
                }
            }
        }
    
    void toSelection(menuItems item, float x, float y, float z)
        {
        highlighted = item;
        // En caso de estar en menú de configuración el cursor es el verde
        if (item == menuItems.backFromConfig ||
            item == menuItems.graphics ||
            item == menuItems.music ||
            item == menuItems.sound )
            {
            selectCursor = GameObject.FindWithTag("SelectCursorConfig");
            }
        // En caso de estar en menú principal el cursor es el rojo
        else
            {
            selectCursor = GameObject.FindWithTag("SelectCursor");
            }
        selectCursor.GetComponent<Transform>().position = new Vector3(x, y, z);
        }

    bool isPressed()
        {
        if (Input.GetAxis("Fire1") != 0 ||
            Input.GetAxis("Vertical") != 0 ||
            Input.GetAxis("Horizontal") != 0)
            {
            return true;
            }
        else
            {
            alreadyPressed = false;
            return false;
            }
        }

    /* Lógica de transición:
     * ---------------------
     * Este código corresponde a las partes que no son menú ni juego. Es decir, transiciones
     * entre los menús o propias escenas guionizadas del juego.
     */
    void transitionLogic()
        {
        switch (actualTransition)
            {
            ///////////////////////////////////////
            // Transiciones desde menú principal //
            ///////////////////////////////////////
            case transitionItems.menuToStart:
                float posXmenuToStart = GetComponent<Transform>().position.x;
                posXmenuToStart = posXmenuToStart - 0.2f;
                GetComponent<Transform>().position = new Vector3(posXmenuToStart, 0, -10);
                if (posXmenuToStart <= 0)
                    {
                    toSelection(menuItems.mrLuis, -6.75f + 38.4f, 2.2f, 0);
                    GetComponent<Transform>().position = new Vector3(0, 0, -10);
                    inMenu = false; inGame = false; inTransition = true; 
                    actualTransition = transitionItems.startDialogue;  
                    }
                break;
            case transitionItems.menuToConfig:
                float posYmenuToConfig = GetComponent<Transform>().position.y;
                posYmenuToConfig = posYmenuToConfig + 0.5f;
                GetComponent<Transform>().position = new Vector3(38.4f, posYmenuToConfig, -10);
                if (posYmenuToConfig >= 10.8f)
                    {
                    toSelection(menuItems.backFromConfig, 31.5f, 7.33f, 0);
                    GetComponent<Transform>().position = menuConfigPosition;
                    inGame = false; inTransition = false; inMenu = true;
                    }
                break;
            case transitionItems.menuToCredits:
                float posYmenuToCredits = GetComponent<Transform>().position.y;
                posYmenuToCredits = posYmenuToCredits - 0.5f;
                GetComponent<Transform>().position = new Vector3(38.4f, posYmenuToCredits, -10);
                if (posYmenuToCredits <= -10.8f)
                    {
                    // La flecha roja no se muestra en el menú de créditos, la muestro fuera de cámara
                    toSelection(menuItems.backFromCredits, 19.2f + 38.4f, -10.8f, 0);
                    GetComponent<Transform>().position = menuCreditsPosition;
                    inGame = false; inTransition = false; inMenu = true;
                    }
                break;
            //////////////////////////////////////////////
            // Transiciones desde menú de configuración //
            //////////////////////////////////////////////
            case transitionItems.configToMenu:
                float posYconfigToMenu = GetComponent<Transform>().position.y;
                posYmenuToConfig = posYconfigToMenu - 0.5f;
                GetComponent<Transform>().position = new Vector3(38.4f, posYmenuToConfig, -10);
                if (posYmenuToConfig <= 0)
                    {
                    toSelection(menuItems.config, 0 + 38.4f, -2, 0);
                    GetComponent<Transform>().position = menuScreenPosition;
                    inGame = false; inTransition = false; inMenu = true;
                    }
                break;
            /////////////////////////////////////////
            // Transiciones desde menú de créditos //
            /////////////////////////////////////////
            case transitionItems.creditsToMenu:
                float posYcreditsToMenu = GetComponent<Transform>().position.y;
                posYcreditsToMenu = posYcreditsToMenu + 0.5f;
                GetComponent<Transform>().position = new Vector3(38.4f, posYcreditsToMenu, -10);
                if (posYcreditsToMenu >= 0)
                    {
                    toSelection(menuItems.credits, 4.8f + 38.4f, -2, 0);
                    GetComponent<Transform>().position = menuScreenPosition;
                    inGame = false; inTransition = false; inMenu = true;
                    }
                break;
            /////////////
            // Escenas //
            /////////////
            case transitionItems.startDialogue:
                // Poner bocadillo de "¡Mierda! ¡Voy a llegar tarde!" con player parado en el 
                // sitio y no empezar hasta que presionamos espacio
                // TO DO
                // Desactivo players seleccionados
                GameObject mrLuis = GameObject.FindWithTag("SelectMrLuis");
                GameObject mrFer = GameObject.FindWithTag("SelectMrFer");
                mrLuis.GetComponent<SpriteRenderer>().enabled = false;
                mrFer.GetComponent<SpriteRenderer>().enabled = false;
                // Desactivo pantalla de menú y cursor
                GameObject startScreen = GameObject.FindWithTag("HallCStart");
                GameObject selectCursor = GameObject.FindWithTag("SelectCursor");
                startScreen.GetComponent<SpriteRenderer>().enabled = false;
                selectCursor.GetComponent<SpriteRenderer>().enabled = false;
                inMenu = false; inTransition = false; inGame = true;
                break;
            default:
                Debug.Log("No hay transición especificada");
                break;
            }
        }

    void makeTransition(bool horizontal, float inc, float dest)
        {
        if (horizontal)
            {
            float posX = GetComponent<Transform>().position.x;
            }
        else
            {
            float posY = GetComponent<Transform>().position.y;
            }
        }

    /* Lógica de juego:
     * ----------------
     * Este código gestiona la cámara durante el juego. Básicamente sigue al jugador en sus
     * andanzas. Sin embargo la lógica del jugador y de los enemigos se ejecutan en scripts
     * propios a cada uno de esos objetos.
     */
    void gameLogic()
        {
        if (!playerSpawned)
            {
            player=(GameObject)Instantiate(player, new Vector3(-2.00f,-0.78f,0f), Quaternion.identity);
            objetivo = player.GetComponent<Transform>();
            playerSpawned = true;
            }
        objetivo = player.GetComponent<Transform>();
        GetComponent<Transform>().position = new Vector3(objetivo.position.x + offset,0,-10);
        }

    }
