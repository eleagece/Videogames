using UnityEngine;
using System.Collections;

public class EndEnemies : MonoBehaviour
{

    void OnTriggerEnter2D(Collider2D other)
    {
        //    Debug.Log("DESTRUYO!!! " + other.gameObject.name);

        GameObject[] allObjects = UnityEngine.Object.FindObjectsOfType<GameObject>();


        foreach (GameObject go in allObjects)
        {
            Debug.Log(go.gameObject.name + " is an active object");

            if (go.gameObject.name == "GenerateCleaner")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "GeneratePaperplane")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "GenerateTechnician")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "GenerateBook")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "GenerateNewsPaper")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "Technician(Clone)")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "Maid(Clone)")
            {
                Destroy(go.gameObject);
            }
            if (go.gameObject.name == "PaperPlane(Clone)")
            {
                Destroy(go.gameObject);
            }
        }




    }
}