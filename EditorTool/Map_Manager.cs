﻿using Newtonsoft.Json.Linq;
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
            createMap.Show();
        }

        /* Act on map selection */
        private void assetList_SelectedIndexChanged(object sender, EventArgs e)
        {
            string file_path_without_extension = "DATA/IMAGES/" + maps_json_config[assetList.SelectedItem.ToString()]["menu_sprite"].Value<string>() + ".";
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
    }
}
