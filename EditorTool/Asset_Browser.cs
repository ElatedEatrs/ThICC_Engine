﻿using NAudio.Wave;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Media;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EditorTool
{
    public partial class Asset_Browser : Form
    {
        List<string> full_loaded_filenames = new List<string>();
        AssetType file_type = AssetType.FONT;
        string file_path = "";
        string file_extension = "";
        string pre_selected_option = "";

        SoundPlayer sound_player = new SoundPlayer();
        UsefulFunctions function_libary = new UsefulFunctions();

        public string selected_file_path { get; set; }

        /* Configure asset list filtering */
        public Asset_Browser(AssetType type_to_select_from, string existing_option = "")
        {
            file_type = type_to_select_from;
            switch (type_to_select_from)
            {
                case AssetType.MODEL:
                    file_path = "DATA/MODELS/";
                    file_extension = "*.SDKMESH";
                    break;
                case AssetType.MESH:
                    file_path = "DATA/MODELS/";
                    file_extension = "*.TXTMESH";
                    break;
                case AssetType.IMAGE:
                    file_path = "DATA/IMAGES/";
                    file_extension = "*.DDS";
                    break;
                case AssetType.SOUND:
                    file_path = "DATA/SOUNDS/";
                    file_extension = "*.WAV";
                    break;
                case AssetType.FONT:
                    file_path = "DATA/FONTS/";
                    file_extension = "*.SPRITEFONT";
                    break;
                default:
                    this.Close();
                    break;
            }
            pre_selected_option = existing_option;

            InitializeComponent();
        }

        /* Fetch asset list on form load */
        private void Asset_Browser_Load(object sender, EventArgs e)
        {
            string[] files = Directory.GetFiles(file_path, file_extension, SearchOption.AllDirectories);
            full_loaded_filenames.Clear();
            assetList.Items.Clear();
            int index_to_default_to = -1;
            foreach (string file in files)
            {
                if (Path.GetFileName(file).Length > 14 && Path.GetFileName(file).Substring(Path.GetFileName(file).Length - 13).ToUpper() == "DEBUG.SDKMESH")
                {
                    continue; //Skip over collision debug meshes
                }
                full_loaded_filenames.Add(file);
                assetList.Items.Add(Path.GetFileNameWithoutExtension(file));
                
                if (assetList.Items[assetList.Items.Count-1].ToString() == pre_selected_option)
                {
                    index_to_default_to = assetList.Items.Count-1;
                }
            }
            assetList.SelectedIndex = index_to_default_to;

            modelPreview.Visible = false;
            imagePreview.Visible = false;
            soundPreview.Visible = false;
            playSoundPreview.Visible = false;
        }

        /* Select the highlighted asset */
        private void selectAsset_Click(object sender, EventArgs e)
        {
            if (assetList.SelectedIndex == -1)
            {
                MessageBox.Show("Please select an asset from the list.");
                return;
            }
            selected_file_path = assetList.SelectedItem.ToString();
            this.Close();
        }

        /* Load asset preview and set active variable to return */
        private void assetList_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (file_type)
            {
                case AssetType.SOUND:
                {
                    function_libary.loadSoundPreview(assetList, sound_player, soundPreview, playSoundPreview);
                    break;
                }
                case AssetType.IMAGE:
                {
                    function_libary.loadImagePreview(assetList, imagePreview);
                    break;
                }
                case AssetType.MODEL:
                {
                    function_libary.loadModelPreview(assetList, modelPreview);
                    break;
                }
                case AssetType.FONT:
                {
                    function_libary.loadFontPreview(assetList, imagePreview);
                    break;
                }
            }

            selected_file_path = assetList.SelectedItem.ToString();
        }

        /* Play sound preview */
        private void playSoundPreview_Click(object sender, EventArgs e)
        {
            function_libary.playSoundPreview(assetList, sound_player);
        }
    }
}
