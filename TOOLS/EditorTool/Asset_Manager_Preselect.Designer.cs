﻿namespace EditorTool
{
    partial class Asset_Manager_Preselect
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openCharacterManager = new System.Windows.Forms.Button();
            this.openVehicleManager = new System.Windows.Forms.Button();
            this.openMapManager = new System.Windows.Forms.Button();
            this.openItemManager = new System.Windows.Forms.Button();
            this.openSoundManager = new System.Windows.Forms.Button();
            this.cupManager = new System.Windows.Forms.Button();
            this.commonModelManager = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // openCharacterManager
            // 
            this.openCharacterManager.Location = new System.Drawing.Point(12, 123);
            this.openCharacterManager.Name = "openCharacterManager";
            this.openCharacterManager.Size = new System.Drawing.Size(270, 31);
            this.openCharacterManager.TabIndex = 10;
            this.openCharacterManager.Text = "Character Manager";
            this.openCharacterManager.UseVisualStyleBackColor = true;
            this.openCharacterManager.Click += new System.EventHandler(this.openCharacterManager_Click);
            // 
            // openVehicleManager
            // 
            this.openVehicleManager.Location = new System.Drawing.Point(12, 86);
            this.openVehicleManager.Name = "openVehicleManager";
            this.openVehicleManager.Size = new System.Drawing.Size(270, 31);
            this.openVehicleManager.TabIndex = 9;
            this.openVehicleManager.Text = "Vehicle Manager";
            this.openVehicleManager.UseVisualStyleBackColor = true;
            this.openVehicleManager.Click += new System.EventHandler(this.openVehicleManager_Click);
            // 
            // openMapManager
            // 
            this.openMapManager.Location = new System.Drawing.Point(12, 12);
            this.openMapManager.Name = "openMapManager";
            this.openMapManager.Size = new System.Drawing.Size(270, 31);
            this.openMapManager.TabIndex = 8;
            this.openMapManager.Text = "Map Manager";
            this.openMapManager.UseVisualStyleBackColor = true;
            this.openMapManager.Click += new System.EventHandler(this.openMapManager_Click);
            // 
            // openItemManager
            // 
            this.openItemManager.Enabled = false;
            this.openItemManager.Location = new System.Drawing.Point(12, 160);
            this.openItemManager.Name = "openItemManager";
            this.openItemManager.Size = new System.Drawing.Size(270, 31);
            this.openItemManager.TabIndex = 11;
            this.openItemManager.Text = "In-Game Item Manager";
            this.openItemManager.UseVisualStyleBackColor = true;
            // 
            // openSoundManager
            // 
            this.openSoundManager.Location = new System.Drawing.Point(12, 197);
            this.openSoundManager.Name = "openSoundManager";
            this.openSoundManager.Size = new System.Drawing.Size(270, 31);
            this.openSoundManager.TabIndex = 12;
            this.openSoundManager.Text = "Shared Global Sounds Manager";
            this.openSoundManager.UseVisualStyleBackColor = true;
            this.openSoundManager.Click += new System.EventHandler(this.openSoundManager_Click);
            // 
            // cupManager
            // 
            this.cupManager.Location = new System.Drawing.Point(12, 49);
            this.cupManager.Name = "cupManager";
            this.cupManager.Size = new System.Drawing.Size(270, 31);
            this.cupManager.TabIndex = 13;
            this.cupManager.Text = "Cup Manager";
            this.cupManager.UseVisualStyleBackColor = true;
            this.cupManager.Click += new System.EventHandler(this.cupManager_Click);
            // 
            // commonModelManager
            // 
            this.commonModelManager.Location = new System.Drawing.Point(12, 234);
            this.commonModelManager.Name = "commonModelManager";
            this.commonModelManager.Size = new System.Drawing.Size(270, 31);
            this.commonModelManager.TabIndex = 14;
            this.commonModelManager.Text = "Common In-Game Models Manager";
            this.commonModelManager.UseVisualStyleBackColor = true;
            this.commonModelManager.Click += new System.EventHandler(this.commonModelManager_Click);
            // 
            // Asset_Manager_Preselect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 273);
            this.Controls.Add(this.commonModelManager);
            this.Controls.Add(this.cupManager);
            this.Controls.Add(this.openSoundManager);
            this.Controls.Add(this.openItemManager);
            this.Controls.Add(this.openCharacterManager);
            this.Controls.Add(this.openVehicleManager);
            this.Controls.Add(this.openMapManager);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Asset_Manager_Preselect";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Asset Groups";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button openCharacterManager;
        private System.Windows.Forms.Button openVehicleManager;
        private System.Windows.Forms.Button openMapManager;
        private System.Windows.Forms.Button openItemManager;
        private System.Windows.Forms.Button openSoundManager;
        private System.Windows.Forms.Button cupManager;
        private System.Windows.Forms.Button commonModelManager;
    }
}