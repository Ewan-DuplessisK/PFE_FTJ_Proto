# Weapon System

- AC_Weapon_User : AC_Interact_User
- AC_Weapon : AC_Interactable
- DA_Weapon
- BP_Projectile

## How to

See examples in `Weapon Test` folder.

### `AC_Weapon_User`
add it for every Actor that's supposed to use/pickup a weapon
- Mesh should have at least `weapon_r_Socket` or a socket defined in `WeaponData`
- Melee animation should have `Melee Attack Begin`, `Melee Attack End` notifies
- Throw animation should have `Throw Weapon` notify

It has Keymapping comment group to overview all actions. You would love to have another one in BP_Character.
Actions: Pickup, Arm, Attack (melee/range dependent on `DA_Weapon.type`), Drop, Throw.

### `AC_Weapon`
add it for weapons (Actors, inherit BP_Weapon or even StaticMesh directly on a Scene)
-  `WeaponData` Data Asset is about a weapon  (instance of `DA_Weapon`)
- Current `Ammo` or leave it default `-1` to get it from from `WeaponData`
- `Collision Radius` is a sphere radius to interact and pickup with weapon. Add your own collision if you want to create custom interaction volume, it will work.

### Some notes about `DA_Weapon`

- `float Ammo` is also the same and for Melee (read it like durability)
- `bool Automatic` holding pressed a fire btn will continue attacking
- `float ProjectileBounciness` setting `0` is turning off `ProjectileMovement.ShouldBound` also
- `float ProjectilesNumber/Scattering` increase it for Shortgun-like weapons to spawn specified projectiles at once
- `bool ThrowEmpty` allows to `Throw Weapon` when `Ammo` is out

### Debug keyboard mapping (LVL_Weapon)
- E - interact
- LMB - fire
- RMB - hit
- F - throw
- G - drop