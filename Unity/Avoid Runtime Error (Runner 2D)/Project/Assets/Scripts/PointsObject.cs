using UnityEngine;
using System.Collections;

public class PointsObject : MonoBehaviour {

    public int points;

    void Start()
    {
        Vector3 pos = transform.position;
        pos.z = 0;
        pos.y = -2.426332f;
        GetComponent<Transform>().position = pos;
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        Debug.Log(other.gameObject.name);
        if (other.gameObject.name == "mainCharacter(Clone)")
        {
            //Enviar mensaje de puntos
            other.gameObject.SendMessage("addPoints", points);
            Destroy(this.gameObject);
        }
    }
}
