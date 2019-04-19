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
    public partial class Map_Manager : Form
    {
        UsefulFunctions common_functions = new UsefulFunctions();
        JObject maps_json_config;
        public Map_Manager()
        {
            InitializeComponent();

            maps_json_config = JObject.Parse(File.ReadAllText("DATA/CONFIGS/MAP_CONFIG.JSON"));
            foreach (var map_config in maps_json_config)
            {
                assetList.Items.Add(map_config.Key.ToString());
            }
        }

        /* Open map creator window */
        private void newMap_Click(object sender, EventArgs e)
        {
            Create_Map createMap = new Create_Map();
            //needs to refresh
            createMap.Show();
        }

        /* Act on map selection */
        private void assetList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (assetList.SelectedIndex == -1)
            {
                return;
            }

            string file_path_without_extension = common_functions.getFolder(AssetType.IMAGE) + maps_json_config[assetList.SelectedItem.ToString()]["menu_sprite"].Value<string>() + ".";
            string file_path_with_extension = "";
            if (File.Exists(file_path_without_extension + "PNG"))
            {
                file_path_with_extension = file_path_without_extension + "PNG";
            }
            else if (File.Exists(file_path_without_extension + "JPG"))
            {
                file_path_with_extension = file_path_without_extension + "JPG";
            }
            else if (File.Exists(file_path_without_extension + "JPEG"))
            {
                file_path_with_extension = file_path_without_extension + "JPEG";
            }
            else
            {
                previewImage.Image = null;
                return;
            }

            using (var tempPreviewImg = new Bitmap(file_path_with_extension))
            {
                previewImage.Image = new Bitmap(tempPreviewImg);
            }
        }

        /* Open map creator window for editing */
        private void editMap_Click(object sender, EventArgs e)
        {
            if (assetList.SelectedIndex == -1)
            {
                MessageBox.Show("Please select a map from the list to edit.", "No map selected.", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            Create_Map editMap = new Create_Map(maps_json_config, assetList.SelectedItem.ToString());
            editMap.Show();
        }

        /* Delete selected map */
        private void deleteMap_Click(object sender, EventArgs e)
        {
            if (assetList.SelectedIndex == -1)
            {
                MessageBox.Show("Please select a map from the list to delete.", "No map selected.", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            //Confirm
            DialogResult showErrorInfo = MessageBox.Show("Are you sure you want to delete this map?", "About to delete selected map...", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (showErrorInfo != DialogResult.Yes)
            {
                return;
            }

            //Remove useage tags
            JToken data_block = maps_json_config[assetList.SelectedItem.ToString()];
            common_functions.removeUseageTag(AssetType.STRING, data_block["friendly_name"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.IMAGE, data_block["menu_sprite"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.MODEL, data_block["model"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.SOUND, data_block["audio"]["background_start"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.SOUND, data_block["audio"]["background"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.SOUND, data_block["audio"]["final_lap_start"].Value<string>(), "map_config");
            common_functions.removeUseageTag(AssetType.SOUND, data_block["audio"]["final_lap"].Value<string>(), "map_config");

            //Remove JToken from config
            maps_json_config.Remove(assetList.SelectedItem.ToString());
            File.WriteAllText("DATA/CONFIGS/MAP_CONFIG.JSON", maps_json_config.ToString(Formatting.Indented));
            MessageBox.Show("Map successfully deleted!", "Deleted.", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
