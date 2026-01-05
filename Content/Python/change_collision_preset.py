import unreal

# CONFIG: change these
NEW_PROFILE_NAME = "BlockAll"
# e.g. "NoCollision", "OverlapAll", "BlockAll", or your custom profile name

def set_collision_for_selected_by_type(profile_name):
    print('"Set collision profile for selected actors', profile_name);
    # get selected actors
    selected = unreal.EditorLevelLibrary.get_selected_level_actors()
    if not selected:
        unreal.log_warning("No actors selected.")
        return

    # start an editor transaction for undo
    try:
        trans = unreal.ScopedEditorTransaction("Set collision profile for selected actors")
    except Exception:
        trans = None

    changed = 0
    for actor in selected:
        print(f"[DEBUG] Actor matched: (class: {actor.get_class().get_name()}) {actor.get_full_name()}")

        comps = actor.get_components_by_class(unreal.PrimitiveComponent)
        print(f"[DEBUG] Found {len(comps)} PrimitiveComponent(s) on {actor.get_name()}")
            
        for comp in comps:
            try:
                print(f"[DEBUG] Processing component: {comp.get_name()} (type: {comp.get_class().get_name()})")

                current_profile = comp.get_collision_profile_name()
                print(f"[DEBUG] Current profile: {current_profile}")

                if current_profile == "Default":
                    # preferred: use API if available
                    if hasattr(comp, "set_collision_profile_name"):
                        print(f"[DEBUG] Using set_collision_profile_name() method")
                        comp.set_collision_profile_name(profile_name)
                        print(f"[DEBUG] Successfully set profile to '{profile_name}' on {comp.get_name()}")
                    else:
                        print(f"[DEBUG] Falling back to set_editor_property()")
                        comp.set_editor_property("collision_profile_name", profile_name)
                        print(f"[DEBUG] Successfully set profile via property on {comp.get_name()}")

                    comp.modify()
                    changed += 1
                else:
                    print(f"[DEBUG] Skipping {comp.get_name()} - profile is '{current_profile}', not 'Default'")

            except Exception as e:
                unreal.log_error(f"Failed to set profile on {actor.get_name()}: {e}")

                unreal.log("Changed collision profile on {} components".format(changed))
                # optionally save the level
                # unreal.EditorLevelLibrary.save_current_level()

# run
set_collision_for_selected_by_type(NEW_PROFILE_NAME)
