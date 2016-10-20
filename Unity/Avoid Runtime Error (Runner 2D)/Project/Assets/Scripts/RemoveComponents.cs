using UnityEngine;
using System.Collections;

public class RemoveComponents : MonoBehaviour {

	

    void OnTriggerEnter2D(Collider2D other)
    {
        Destroy(other.gameObject);

    }

 
}


