using UnityEngine;
using System.Collections;

public class Cleaner : MonoBehaviour {


    // Use this for initialization
    void Start()
    {
        Vector3 pos = transform.position;
        pos.z = 0;
        pos.y = -2.426332f;
        GetComponent<Transform>().position = pos;
    }


    void OnTriggerEnter2D(Collider2D other){
        if (other.gameObject.name == "mainCharacter(Clone)")
        {
            other.gameObject.SendMessage("changeSpeed", 3f);
            GetComponent<Animator>().SetBool("isAngry", true);
        }


    }

    void OnTriggerExit2D(Collider2D other)
    {
        if (other.gameObject.name == "mainCharacter")
        {
            other.gameObject.SendMessage("changeSpeed", 8f);
        }
    }


}
