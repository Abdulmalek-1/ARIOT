using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;
using UnityEngine.Networking;

public class Fan : MonoBehaviour
{
    public VirtualButtonBehaviour Vb_high;
    public VirtualButtonBehaviour Vb_medium;
    public VirtualButtonBehaviour Vb_low;
    public VirtualButtonBehaviour Vb_off;
    public string url_high;
    public string url_medium;
    public string url_low;
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
        Vb_high.RegisterOnButtonPressed(HighButtonPressed_high);

        Vb_medium.RegisterOnButtonPressed(MediumButtonPressed_medium);

        Vb_low.RegisterOnButtonPressed(LowButtonPressed_low);

        Vb_off.RegisterOnButtonPressed(OnButtonPressed_off);

    }
    public void HighButtonPressed_high(VirtualButtonBehaviour Vb_high)
    {
        StartCoroutine(GetRequest(url_high));
        Debug.Log("FAN IS HIGH");
    }
    public void MediumButtonPressed_medium(VirtualButtonBehaviour Vb_medium)
    {
        StartCoroutine(GetRequest(url_medium));
        Debug.Log("FAN IS MEDIUM");
    }
    public void LowButtonPressed_low(VirtualButtonBehaviour Vb_low)
    {
        StartCoroutine(GetRequest(url_low));
        Debug.Log("FAN IS LOW");
    }

    public void OnButtonPressed_off(VirtualButtonBehaviour Vb_off)
    {
        StartCoroutine(GetRequest(url_off));
        Debug.Log("FAN IS OFF");
    }

}