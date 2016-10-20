using UnityEngine;
using System.Collections;

public class Technician : MonoBehaviour {


	public float speed = 1f;
    // Use this for initialization
    void Start () {
        speed = 7f;
        Vector3 pos = transform.position;
        pos.z = 0;
        pos.y = -2.426332f;
        GetComponent<Transform>().position = pos;
        StartCoroutine(follow());
    }

    // Update is called once per frame
    void Update()
    {
            Vector3 pos = transform.position;
            pos.x += 1.7f * speed * Time.deltaTime;
            transform.position = pos;
    }


    void OnTriggerEnter2D(Collider2D other) {
        if (other.gameObject.name == "mainCharacter(Clone)")
        {
            GetComponent<Animator>().SetBool("reprimand", true);
            other.gameObject.SendMessage("reprimand");
            StartCoroutine(reprimand(other));
        }
        }

 
    IEnumerator follow()
    {
        yield return new WaitForSeconds(5);
        GetComponent<Animator>().SetBool("fall", true);
        speed = 7f;
        StartCoroutine(fall());
    }


    IEnumerator reprimand(Collider2D other)
    {
        speed = 0f;
        yield return new WaitForSeconds(3);
        other.gameObject.SendMessage("run");
        yield return new WaitForSeconds(3);
        Destroy(this.gameObject);
    }

    IEnumerator fall()
    {
        yield return new WaitForSeconds(3);
        speed = 0f;
        Destroy(this.gameObject);
    }
}
