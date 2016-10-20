using UnityEngine;
using System.Collections;

public class Scripts : MonoBehaviour {

	public Transform objetivo;
	public float offset = 2f;

	// Update is called once per frame
	void Update () {
		GetComponent<Transform> ().position = new Vector3 (objetivo.position.x + offset, GetComponent<Transform> ().position.y, GetComponent<Transform> ().position.z);
	}
}
