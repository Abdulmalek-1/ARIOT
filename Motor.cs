using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;
using UnityEngine.Networking;

public class Motor : MonoBehaviour
{
    public VirtualButtonBehaviour Vb_up;
    public VirtualButtonBehaviour Vb_down;
    public VirtualButtonBehaviour Vb_off;
    public string url_up;
    public string url_down;
    public string url_off;

    IEnumerator GetRequest(string uri)
    {
        using (UnityWebRequest webRequest = UnityWebRequest.Get(uri))
        {
            // Request and wait for the desired page.
            yield return webRequest.SendWebRequest();

        }
    }

    void Start()
    {
        Vb_up.RegisterOnButtonPressed(OnButtonPressed_up);
        Vb_down.RegisterOnButtonPressed(OnButtonPressed_down);
        Vb_off.RegisterOnButtonPressed(OnButtonPressed_off);

    }


    public void OnButtonPressed_up(VirtualButtonBehaviour Vb_up)
    {
        StartCoroutine(GetRequest(url_up));
        Debug.Log("UP IS ON");
    }
    public void OnButtonPressed_down(VirtualButtonBehaviour Vb_down)
    {
        StartCoroutine(GetRequest(url_down));
        Debug.Log("DOWN IS ON");
    }

    public void OnButtonPressed_off(VirtualButtonBehaviour Vb_off)
    {
        StartCoroutine(GetRequest(url_off));
        Debug.Log("STEPPER IS OFF");
    }

}