using UnityEngine;
using System.Collections;

public class EndGame : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	

    void OnTriggerEnter2D(Collider2D other)
    {
        Debug.Log("TRIGGERRR");
        GetComponent<Collider2D>().isTrigger = false;
        if (other.gameObject.name == "mainCharacter(Clone)")
        {
            other.gameObject.SendMessage("end");
        }  
      
    }


}
