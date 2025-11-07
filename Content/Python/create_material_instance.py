import unreal
import os

# unreal.log("hello, world")

material_dict = {
    "Default": "/Game/MaterialBase/MaterialInstance/MI_Default.MI_Default",
    "AlphaTest": "/Game/MaterialBase/MaterialInstance/MI_AlphaTest.MI_AlphaTest",
    "Emissive": "/Game/MaterialBase/MaterialInstance/MI_Emissive.MI_Emissive",
    "Transparent": "/Game/MaterialBase/MaterialInstance/MI_Transparency.MI_Transparency",
    "Decal": "/Game/MaterialBase/MaterialInstance/MI_Decal.MI_Decal"
}
texture_dict = {
    "Default": ["_C", "_N", "_ORM"],
    "AlphaTest": ["_C", "_N", "_ORM", "_Mask"],
    "Emissive": ["_C", "_N", "_ORM", "_Emissive"],
    "Transparent": ["_C", "_N", "_ARM"],
    "Decal": ["_C", "_N", "_ARM"]
}

material_parameter_dict = {"_C": "BaseColor_Tex", "_N": "Normal_Tex", "_ORM": "ORM_Tex", "_ARM": "ARM_Tex", "_Emissive": "Emissive_Tex", "_Mask": "Mask_Tex"}

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
editor_asset_lib = unreal.EditorAssetLibrary()

def get_static_mesh():
    mesh_list = [] 
    sel_assets = unreal.EditorUtilityLibrary.get_selected_assets()

    for asset in sel_assets:
        # asset_name = asset.get_name()
        # asset_folder = unreal.Paths.get_path(asset.get_path_name())
        if asset.get_class().get_name() == "StaticMesh":
            mesh_list.append(asset)
    
    return mesh_list

def main():
    mesh_list = get_static_mesh()
    print(mesh_list)
    for mesh in mesh_list:
        mesh_path = mesh.get_path_name()
        mesh_folder =  unreal.Paths.get_path(mesh.get_path_name())
        material_folder = mesh_folder.replace("Meshes", "Materials")
        texture_folder = mesh_folder.replace("Meshes", "Textures")
        
        sm_component = unreal.StaticMeshComponent()
        sm_component.set_static_mesh(mesh)
        material_slots = sm_component.get_material_slot_names()

        # load mesh
        loaded_mesh = editor_asset_lib.load_asset(mesh_path)

        for index, slot in enumerate(material_slots):
            slot_name = str(slot)
            # print(slot_name)
            texture_name = "_".join(slot_name.split("_")[1:-1])
            mi_name = "MI_"+ texture_name + "_00"
            mat_type = slot_name.split("_")[-1]

            base_material_path = material_dict[mat_type]
            base_material = editor_asset_lib.load_asset(base_material_path) # load material

            # create material instance if it doesn't exist
            mi_path = os.path.join(material_folder, mi_name)
            if editor_asset_lib.does_asset_exist(mi_path):
                mi = editor_asset_lib.load_asset(mi_path)
            else:
                mi = asset_tools.create_asset(
                    asset_name=mi_name,
                    package_path=material_folder,
                    asset_class=unreal.MaterialInstanceConstant,
                    factory=unreal.MaterialInstanceConstantFactoryNew()
                )

            # set parent material
            mi.set_editor_property("parent", base_material)

            # get textures' names and paths
            tex_list = texture_dict[mat_type]
            for tex_type in tex_list:
                tex_name = "T_" + texture_name + tex_type
                tex_path = os.path.join(texture_folder, tex_name)
                if not editor_asset_lib.does_asset_exist(tex_path):
                    continue
                
                tex = editor_asset_lib.load_asset(tex_path)
                mi_parameter = material_parameter_dict[tex_type]
                unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(mi, mi_parameter, tex)
            
            


            # C_tex_name = "T_" + texture_name + "_C"
            # N_tex_name = "T_" + texture_name + "_N"
            # ORM_tex_name = "T_" + texture_name + "_ORM"

            # C_tex_path = os.path.join(texture_folder, C_tex_name)
            # N_tex_path = os.path.join(texture_folder, N_tex_name)
            # ORM_tex_path = os.path.join(texture_folder, ORM_tex_name)
            
            # load parent material, texture and static mesh
            # C_tex = editor_asset_lib.load_asset(C_tex_path)
            # N_tex = editor_asset_lib.load_asset(N_tex_path)
            # ORM_tex = editor_asset_lib.load_asset(ORM_tex_path)




            # unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(mi, "BaseColor_Tex", C_tex)
            # unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(mi, "Normal_Tex", N_tex)
            # unreal.MaterialEditingLibrary.set_material_instance_texture_parameter_value(mi, "ORM_Tex", ORM_tex)

            editor_asset_lib.save_loaded_asset(mi)
            mesh.set_material(index, mi)
            editor_asset_lib.save_loaded_asset(loaded_mesh)


        print(material_slots)

main()