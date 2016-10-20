using UnityEngine;
using System.Collections;

public class GeneratorElements : MonoBehaviour {

    public GameObject[] obj;
    public float minTime = 4f;
    public float maxTime = 7f;
    public int minHeight;
    public int maxHeight;
    public bool firstTime = true;
    public bool generating = false;
    public float positionFinal;

    void Update()
    {
        if (Input.GetAxis("Jump") > 0)
            {
            generating = true;
            }
        if(firstTime && generating)
        {
            generate();
            firstTime = false;
        }
    }

    void generate()
    {

        if(GetComponent<Transform>().position.y < this.positionFinal)
        {
            Vector3 pos = transform.position;
            float previousY = GetComponent<Transform>().position.y;
            pos.y = GetComponent<Transform>().position.y + Random.Range(minHeight, maxHeight);
            transform.position = pos;
            Instantiate(obj[Random.Range(0, obj.Length)], transform.position, Quaternion.identity);
            pos.y = previousY;
            pos.z = 0;
            GetComponent<Transform>().position = pos;
            Invoke("generate", Random.Range(minTime, maxTime));
        }

    }
}
