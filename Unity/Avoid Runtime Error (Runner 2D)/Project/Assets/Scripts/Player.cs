using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour
{
    bool listenToMessage = true;

    public float jump = 15f;
    bool isJumping = false;
    public float speed = 0f;
    bool isRun = false;
    int NSaltos = 0;
    public int totalPoints = 0;
    bool notEnd = true;
    private float timeLeft = 0;
    // Use this for initialization
    void Start()
    {
        speed = 12f;
        isRun = false;
        GetComponent<Animator>().SetBool("stop", true);
    }

    void FixedUpdate()
    {

        if (notEnd)
        {
            if (isRun)
            {
                GetComponent<Rigidbody2D>().velocity = new Vector2(this.speed, GetComponent<Rigidbody2D>().velocity.y);
            }
        }
    }


    // Update is called once per frame
    void Update()
    {

        if (notEnd)
        {
            if (this.isRun)
            {
                if (Input.GetAxis("Jump") > 0)
                {
                    this.NSaltos += 1;
                    if (this.NSaltos == 1)
                    {
                        this.isJumping = true;
                        GetComponent<Animator>().SetBool("jumping", true);
                        GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, jump);

                    }

                };
            }
            else
            {
                if (Input.GetAxis("Jump") > 0)
                    run();
            }
        }
    }


    void OnTriggerEnter2D(Collider2D other)
    {
        this.NSaltos = 0;
        this.isJumping = false;
        GetComponent<Animator>().SetBool("jumping", false);
    }



    /**Acciones con los tecnico**/
    public void reprimand()
    {
        this.isRun = false;
        this.isJumping = false;
        this.speed = 0f;
        GetComponent<Animator>().SetBool("stop", true);
    }

    public void run()
    {
        this.speed = 12f;
        this.isRun = true;
        GetComponent<Animator>().SetBool("stop", false);
        GetComponent<Animator>().SetBool("isHit", false);

    }


    /**Acciones con las señoras de la limpieza**/
    public void changeSpeed(float speed)
    {
        this.speed = speed;

    }

    /**Accion con los aviones de papel**/
    public void push()
    {
        GetComponent<Animator>().SetBool("isHit", true);
        this.speed = -10f;
        this.isRun = true;
        this.isJumping = false;

    }


    /**Accion con libros y periodicos**/
    public void addPoints(int points)
    {
        this.totalPoints = this.totalPoints + points;

    }


    public void setTime(float timeLeft)
        {
        Debug.Log("Tiempo restante en la funcion: " + timeLeft);
        this.timeLeft = timeLeft;
        }

    /**Accion al llegar al final**/
    public void end()
        {
        Debug.Log("END ACTIONS");
        this.notEnd = false;
        Vector3 pos = transform.position;
        GetComponent<Transform>().position = pos;
        this.isRun = false;
        this.isJumping = false;
        this.speed = 0f;
        GetComponent<Animator>().SetBool("stop", true);

        // OBTENCIÓN DE GAMEOBJECTS PARA MOSTRAR LA NOTA
        // Objeto globo de dialogo
        GameObject bubble = GameObject.FindWithTag("Bubble");
        // Objetos que indican si hemos llegado tarde o no
        GameObject late = GameObject.FindWithTag("Late");
        GameObject inTime = GameObject.FindWithTag("InTime");
        // Objetos que indican lo que hemos estudiado
        GameObject poco = GameObject.FindWithTag("Poco");
        GameObject bastante = GameObject.FindWithTag("Bastante");
        GameObject mucho = GameObject.FindWithTag("Mucho");
        GameObject muchisimo = GameObject.FindWithTag("Muchisimo");
        // Objetos que indican la nota
        GameObject suspenso = GameObject.FindWithTag("SS");
        GameObject aprobado = GameObject.FindWithTag("AP");
        GameObject notable = GameObject.FindWithTag("NT");
        GameObject sobresaliente = GameObject.FindWithTag("SB");
        GameObject matricula = GameObject.FindWithTag("MH");
        
        // SE MUESTRA NOTA
        // Aparece globo
        bubble.GetComponent<SpriteRenderer>().enabled = true;
        // Cálculo de lo que ha estudiado el alumno
        Debug.Log("Lo que ha estudiado el alumno");
        if (this.totalPoints <= 6)
            {
            Debug.Log("Poco");
            poco.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints == 7)
            {
            Debug.Log("Bastante");
            bastante.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints == 8)
            {
            Debug.Log("Mucho");
            mucho.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints >= 9)
            {
            Debug.Log("Muchisimo");
            muchisimo.GetComponent<SpriteRenderer>().enabled = true;
            }
        // Factor de corrección si se llega tarde o pronto
        Debug.Log("Si llega tarde o pronto");
        if (timeLeft>0)
            {
            Debug.Log("Pronto");
            inTime.GetComponent<SpriteRenderer>().enabled = true;
            totalPoints = totalPoints + 1;
            }
        else
            {
            Debug.Log("Tarde");
            late.GetComponent<SpriteRenderer>().enabled = true;
            totalPoints = totalPoints - 3;
            }
        // Nota final
        Debug.Log("Nota final");
        if (this.totalPoints <= 4)
            {
            Debug.Log("SS");
            suspenso.GetComponent<SpriteRenderer>().enabled = true;
            }
        if (this.totalPoints >= 5 && this.totalPoints <= 6)
            {
            Debug.Log("AP");
            aprobado.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints >= 7 && this.totalPoints <= 8)
            {
            Debug.Log("NT");
            notable.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints >= 9 && this.totalPoints <=10)
            {
            Debug.Log("SB");
            sobresaliente.GetComponent<SpriteRenderer>().enabled = true;
            }
        else if (this.totalPoints >= 11)
            {
            Debug.Log("MH");
            matricula.GetComponent<SpriteRenderer>().enabled = true;
            }
        }
    }