﻿using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EditorTool
{
    public partial class Create_Vehicle : Form
    {
        UsefulFunctions function_libary = new UsefulFunctions();

        /* If editing, load data */
        JObject maps_json_config = null;
        string map_json_key = "";
        bool edit_mode = false;
        public Create_Vehicle(JObject json_data = null, string object_key = "")
        {
            maps_json_config = json_data;
            map_json_key = object_key;
            edit_mode = (json_data != null && object_key != "");

            InitializeComponent();
        }

        /* On Load */
        private void Create_Vehicle_Load(object sender, EventArgs e)
        {
            if (edit_mode)
            {
                // If in edit mode, load existing config
                mapCodename.Text = map_json_key;
                mapCodename.ReadOnly = true;
                mapName.Text = maps_json_config[map_json_key]["friendly_name"].Value<string>();
                mapPreviewImage.Text = maps_json_config[map_json_key]["menu_sprite"].Value<string>();
                mapModelAsset.Text = maps_json_config[map_json_key]["model"].Value<string>();
            }
        }

        /* Select assets */
        private void loadString_Click(object sender, EventArgs e)
        {
            function_libary.assetSelectHandler(mapName, AssetType.STRING);
        }
        private void selectImageAsset_Click(object sender, EventArgs e)
        {
            function_libary.assetSelectHandler(mapPreviewImage, AssetType.IMAGE);
        }
        private void selectMapModel_Click(object sender, EventArgs e)
        {
            function_libary.assetSelectHandler(mapModelAsset, AssetType.MODEL);
        }

        /* Save vehicle to config */
        private void saveMap_Click(object sender, EventArgs e)
        {
            //All inputs required
            if (mapCodename.Text == "" || mapName.Text == "" || mapPreviewImage.Text == "" || mapModelAsset.Text == "")
            {
                MessageBox.Show("Please complete all fields before trying to save.", "Can't save.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //Update tags
            function_libary.executeUseageQueueForTag(function_libary.getUseageTagFor(AssetCompType.VEHICLE));

            //Load existing config if not editing (would already be loaded)
            if (!edit_mode)
            {
                maps_json_config = JObject.Parse(File.ReadAllText("DATA/CONFIGS/VEHICLE_CONFIG.JSON"));
            }

            string map_name = mapCodename.Text;

            //Add to config
            if (!edit_mode) { maps_json_config[map_name] = JObject.Parse("{}"); }
            maps_json_config[map_name]["friendly_name"] = mapName.Text;
            maps_json_config[map_name]["menu_sprite"] = mapPreviewImage.Text;
            maps_json_config[map_name]["model"] = mapModelAsset.Text;
            maps_json_config[map_name]["audio"] = JObject.Parse("{}");

            //Save back out
            File.WriteAllText("DATA/CONFIGS/VEHICLE_CONFIG.JSON", maps_json_config.ToString(Formatting.Indented));

            //Done
            MessageBox.Show("Saved vehicle configuration!", "Saved.", MessageBoxButtons.OK, MessageBoxIcon.Information);
            this.Close();
        }
    }
}
