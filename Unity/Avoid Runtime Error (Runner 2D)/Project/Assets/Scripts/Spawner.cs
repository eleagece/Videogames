using UnityEngine;
using System.Collections;
using UnityEngine.UI;
/*
 * Spawner.cs
 * ----------
 * -Script asociado a Main Camera
 * -Genera nuevos pasillos o clases dependiendo de distintos factores
 */

public class Spawner : MonoBehaviour 
	{    
    public int prefabsPerZone=5;  // Indica cuántos pasillos/clases tiene cada zona (2<=prefabsPerZone<infinito)
    public GameObject[] corridors;  // Prefabs de pasillos que voy a spawnear
	public GameObject[] classes;  // Prefabas de clases que voy a spawnear
    public GameObject[] transitions;  // Prefabs de transición entre clase-pasillo (0) y pasillo-clase (1)
    public GameObject[] finalZones;  // Zonas a las que se entra cuando queda poco tiempo
	public GameObject finalClass;  // Clase final (final del juego)
	public float timeLeft=60f;  // Indica el tiempo que queda en segundos
    public Text timeLeftText;  // El texto que muestra el tiempo que queda en segundos

    private System.Random rnd = new System.Random();
    private bool oldSchoolMode = false;  // Indica si los gráficos lucen antiguos
    private bool allGenerated = false;  // Indica si se han generado todos los escenarios para que deje de mirar los spawners
    private bool timerOn = false;  // Indica si ha empezado la cuenta atrás
    private int spawned=1;  // Indica cuántos pasillos/clases llevamos spawneados. Nos sirve para saber en que posición spawneamos
    private int spawnedInZone=1;  // Indica cuántos pasillos/clases llevamos spawneados dentro de la zona actual
    private bool inFinalZone=false;  // Indica si estamos en zona final antes de llegar a la presentación
    private bool inCorridor=true;  // Indica si estamos en zona de pasillos (true) o clases (false)
	private float hallLong=38.4f;  // Largo del 'hall'. Nos sirve para tener el offset a partir de donde generamos pasillos/clases
	private float zoneLong=19.2f;  // Largo de una zona 'pasillo' o 'clase'

	void Start () 
		{
		Debug.Log("Spawner preparado");
		// El hall ya está cargado de manera predeterminada en la escena
		}

	void Update()
		{
        updateTimer();
		}

	void OnTriggerEnter2D (Collider2D other)
		{
        if (!allGenerated)
            {
            if (other.tag == "StartTimer")
                {
                Debug.Log("Empieza cuenta atrás");
                timeLeftText.text = timeLeft.ToString("f0");
                timerOn = true;
                }
            else if (other.tag == "ScenarioSpawner")
                {
                float x=(zoneLong * spawned)+hallLong;
                Debug.Log("******************* Spawn " + spawned + " *******************"); 
                Debug.Log("Posición: " + x);
		        Vector3 nextPrefabPosition= new Vector3 (x, 0, 0);
		        Spawn(nextPrefabPosition);
		        }
            else if (other.tag == "ScenarioDestroyer")
                {
                // ¿Cómo hacer para destruir padres y poder meter el collider en el hijo?
                Destroy(other.gameObject);
                }
            }
        else if (allGenerated)
            {
            if (other.tag == "CheckInTime")
                {
                Debug.Log("Entró en clase en "+timeLeft);
                GameObject player;
                player = GameObject.FindWithTag("MainCharacter");
                player.SendMessage("setTime", this.timeLeft);
                }
            else if (other.tag == "Ending")
                {
                Debug.Log("¡¡FINAL!!");
                //**********************
                // MANDAR MENSAJE AL DIRECTOR Y AL PLAYER PARA QUE SE PAREN 
                // A EJECUTAR SUS ACCIONES FINALES
                //**********************
                //resetValues();
                }
            }   
        }

	void Spawn(Vector3 nextPrefabPosition)
		// Spawnea un pasillo o clase en la posición 'pos' dependiendo de distintos factores
		{
		spawned++;
        if (timeLeft<16 && !inFinalZone)  // Si el tiempo baja de 16 segundos tenemos que spawnear zona pre final
            {
            inFinalZone = true;
            if (inCorridor)
                {
                Debug.Log("Prefab: zona final 0");
                Instantiate(finalZones[0], nextPrefabPosition, Quaternion.identity);
                }
            else
                {
                Debug.Log("Prefab: zona final 1");
                Instantiate(finalZones[1], nextPrefabPosition, Quaternion.identity);
                }
            }
        else if (timeLeft<16 && inFinalZone)  // Si ya la zona final está spawneda spawneamos clase de DVI y bloqueamos spawns
            {
            allGenerated = true;
            Debug.Log("Prefab: clase de DVI");
            //**********************
            // OJO QUE SI VA MUY RÁPIDO SE PUEDE SALTAR EL COLLIDER QUE GENERA CLASE DE DVI
            //**********************
            nextPrefabPosition.x = nextPrefabPosition.x + 57.6f;
            Instantiate(finalClass, nextPrefabPosition, Quaternion.identity);
            }
        else if (spawnedInZone==prefabsPerZone+1)  // Si ya hemos completado una zona de pasillos/clases empezamos con otra
            {
            spawnedInZone = 1;  // Reseteo de la zona
            Debug.Log("Prefab: transición");
            Instantiate (transitions[transitionZone()], nextPrefabPosition, Quaternion.identity);  // Creamos pasillos
            }
        else  // Si no continuamos generando de la misma zona de pasillos/clases
            {
            if (inCorridor)
                {
                Debug.Log("Prefab: pasillo");
                Instantiate(corridors[rnd.Next(0,5)], nextPrefabPosition, Quaternion.identity);
                }
            else
                {
                Debug.Log("Prefab: clase");
                Instantiate(classes[rnd.Next(0,1)], nextPrefabPosition, Quaternion.identity);
                }
            spawnedInZone++;
            }
        }

    int transitionZone()
        {
        if (inCorridor)
            {
            inCorridor = false;
            return 1;
            }
        else
            {
            inCorridor = true;
            return 0;
            }
        }

    void resetValues()
        {
        timeLeft = 60f;
        allGenerated = false;
        timerOn = false;
        spawned = 1;
        spawnedInZone = 1;
        inFinalZone = false;
        inCorridor = true;
        }

	void updateTimer()
        {
        if (timerOn)
            {
            timeLeft -= Time.deltaTime;
            timeLeftText.text = timeLeft.ToString("f0");
            }
        }
    }