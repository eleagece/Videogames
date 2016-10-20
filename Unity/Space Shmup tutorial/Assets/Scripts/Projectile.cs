﻿using UnityEngine;
using System.Collections;
public class Projectile : MonoBehaviour
{
    [SerializeField]
    private WeaponType _type;
    BoxCollider2D _collider;
    // This public property masks the field _type & takes action when it is set
    public WeaponType type
    {
        get
        {
            return (_type);
        }
        set
        {
            SetType(value);
        }
    }
    void Awake()
    {
        // Test to see whether this has passed off screen every 2 seconds
        _collider = GetComponent<BoxCollider2D>();
        InvokeRepeating("CheckOffscreen", 2f, 2f);
    }
    public void SetType(WeaponType eType)
    {
        // Set the _type
        _type = eType;
        WeaponDefinition def = Main.GetWeaponDefinition(_type);
        Renderer renderer = GetComponent<Renderer>();
        renderer.material.color = def.projectileColor;
    }
    void CheckOffscreen()
    {
        if (Utils.ScreenBoundsCheck
        (_collider.bounds,
        BoundsTest.offScreen) != Vector3.zero)
        {
            Destroy(this.gameObject);
        }
    }
}