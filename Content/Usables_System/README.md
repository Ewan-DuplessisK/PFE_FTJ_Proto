# Weapon System

- AC_Weapon_User : AC_Pickup_User : AC_Interact_User
- AC_Weapon : AC_Pickupable : AC_Interactable
- DA_Weapon
- BP_Projectile

## How to create a Weapon

See examples in `Weapon Test` folder.

- Inherit `DA_Weapon` to desribe a weapon

Steps to create a weapon:
- Create a folder in `/Weapons/` with its name.
- Inherit `DA_Weapon` or copy `DA_W_DefaultWeapon` to describe a weapon.
- Inherit a Blueprint from `BP_Weapon`. It will already contain few components:
- - `StaticMeshComponent`. Set up `StaticMesh` property.
- - `AC_Weapon`. Adjust `WeaponData` and current `Ammo` if you need it to be different from the default.

Also it's possible to add `AC_Weapon` directly to a `StaticMeshActor` on a `Level` to speed up a testing or if it's unique.

As soon as `AC_Weapon` inherits `AC_Interactable` and `AC_Pickupable` it has all them properties that are described further.

## Notes

### `AC_Weapon`
Add this component to weapons (Actors inheriting from `BP_Weapon` or even directly using a `StaticMesh` in a scene).
- `WeaponData` is a Data Asset that defines weapon properties (an instance of `DA_Weapon`).
- `Ammo` can be set manually or left at the default `-1` to use the value from `WeaponData`.

### `AC_Interactable`
could be any item that supposed to be interactable with overlapping and triggering action.
- `float Collision Radius` defines the sphere radius used for interacting with and picking up the weapon. You can add your own collision component to create a custom interaction volume—it will still work.
- `text Title` is a name for widget
- `Widget` is displaying its name
- `bool Interactable?`. Modify in runtime if you need.

### `AC_Pickupable`
could be an item that you prefer to withdraw from a Level like keys, hearts etc.
It's not fully implemented yet because game design doesn't need it.
- `bool Inventoryable?` Save it for further usage.

### `DA_Weapon`
- `float Ammo` applies to both ranged and melee weapons (think of it as durability for melee).
- `bool Automatic`: when true, holding the fire button continues attacking.
- `float ProjectileBounciness`: setting this to `0` disables `ProjectileMovement.ShouldBounce`.
- `float ProjectilesNumber` / `Scattering`: increase these for shotgun-like weapons to spawn multiple projectiles at once.
- `bool ThrowEmpty`: allows the player to throw the weapon even when `Ammo` is depleted.

### `AC_Weapon_User`
Add this component to any Actor that should be able to use or pick up a weapon.
- The mesh should have at least a `weapon_r_Socket` or a socket defined in `WeaponData`.
- Melee animations should include `Melee Attack Begin` and `Melee Attack End` notifies.
- Throw animations should include a `Throw Weapon` notify.

This component includes a Keymapping comment group to provide an overview of all actions. You may want to replicate this in `BP_Character`.
Actions: Pickup, Arm, Attack (melee/ranged based on `DA_Weapon.type`), Drop, Throw.


### Debug keyboard mapping (LVL_Weapon)
- E - interact
- LMB - fire
- RMB - hit
- F - throw
- G - drop