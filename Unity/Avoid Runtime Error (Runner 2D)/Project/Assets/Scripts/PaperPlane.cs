using UnityEngine;
using System.Collections;

public class PaperPlane : MonoBehaviour {

	public float speed = 4f;
	public float stablished = 1.409699f-1.378211f;
    public bool hasHit = false;
    // Use this for initialization
    // Use this for initialization
    void Start()
    {
        Vector3 pos = transform.position;
        pos.z = 0;
        pos.y = -2.426332f;
        GetComponent<Transform>().position = pos;
    }


    void OnTriggerEnter2D(Collider2D other) {
       if(other.gameObject.name == "mainCharacter(Clone)")
        {
            hasHit = true;
            other.gameObject.SendMessage("push");
            StartCoroutine(timer(other));
        }
	}

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = transform.position;
        pos.x +=  -speed * Time.deltaTime;
        if (hasHit)
        {
            pos.y += speed * Time.deltaTime;

        }
        transform.position = pos;
    }


	IEnumerator timer(Collider2D other)
    {
		yield return new WaitForSeconds (1f);
        other.gameObject.SendMessage("run");
    }
}
