﻿namespace EditorTool
{
    partial class Model_Importer_MaterialEditor
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
            this.materialPreview = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.materialName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.isTransparent = new System.Windows.Forms.CheckBox();
            this.transparencySlider = new System.Windows.Forms.TrackBar();
            this.inPlayableArea = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.domainUpDown1 = new System.Windows.Forms.DomainUpDown();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBar2 = new System.Windows.Forms.TrackBar();
            this.label6 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.diffuseMapBrowse = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.diffuseMap = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.ambientMapBrowse = new System.Windows.Forms.Button();
            this.ambientMap = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.specularMapBrowse = new System.Windows.Forms.Button();
            this.specularMap = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.normalMapBrowse = new System.Windows.Forms.Button();
            this.normalMap = new System.Windows.Forms.TextBox();
            this.diffuseColour = new System.Windows.Forms.PictureBox();
            this.label11 = new System.Windows.Forms.Label();
            this.diffuseColourBrowse = new System.Windows.Forms.Button();
            this.ambientColourBrowse = new System.Windows.Forms.Button();
            this.label12 = new System.Windows.Forms.Label();
            this.ambientColour = new System.Windows.Forms.PictureBox();
            this.specularColourBrowse = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.specularColour = new System.Windows.Forms.PictureBox();
            this.emissiveColourBrowse = new System.Windows.Forms.Button();
            this.label14 = new System.Windows.Forms.Label();
            this.emissiveColour = new System.Windows.Forms.PictureBox();
            this.label15 = new System.Windows.Forms.Label();
            this.onTrack = new System.Windows.Forms.RadioButton();
            this.offTrack = new System.Windows.Forms.RadioButton();
            this.boostPad = new System.Windows.Forms.RadioButton();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.materialPreview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.transparencySlider)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.diffuseColour)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ambientColour)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.specularColour)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emissiveColour)).BeginInit();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // materialPreview
            // 
            this.materialPreview.Location = new System.Drawing.Point(12, 12);
            this.materialPreview.Name = "materialPreview";
            this.materialPreview.Size = new System.Drawing.Size(300, 300);
            this.materialPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.materialPreview.TabIndex = 15;
            this.materialPreview.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 13);
            this.label1.TabIndex = 16;
            this.label1.Text = "Material Name";
            // 
            // materialName
            // 
            this.materialName.Location = new System.Drawing.Point(9, 36);
            this.materialName.Name = "materialName";
            this.materialName.ReadOnly = true;
            this.materialName.Size = new System.Drawing.Size(285, 20);
            this.materialName.TabIndex = 17;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 152);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "Transparency";
            // 
            // isTransparent
            // 
            this.isTransparent.AutoSize = true;
            this.isTransparent.Location = new System.Drawing.Point(211, 151);
            this.isTransparent.Name = "isTransparent";
            this.isTransparent.Size = new System.Drawing.Size(83, 17);
            this.isTransparent.TabIndex = 19;
            this.isTransparent.Text = "Transparent";
            this.isTransparent.UseVisualStyleBackColor = true;
            // 
            // transparencySlider
            // 
            this.transparencySlider.LargeChange = 1;
            this.transparencySlider.Location = new System.Drawing.Point(9, 171);
            this.transparencySlider.Name = "transparencySlider";
            this.transparencySlider.Size = new System.Drawing.Size(285, 45);
            this.transparencySlider.TabIndex = 20;
            // 
            // inPlayableArea
            // 
            this.inPlayableArea.AutoSize = true;
            this.inPlayableArea.Location = new System.Drawing.Point(6, 19);
            this.inPlayableArea.Name = "inPlayableArea";
            this.inPlayableArea.Size = new System.Drawing.Size(114, 17);
            this.inPlayableArea.TabIndex = 22;
            this.inPlayableArea.Text = "Is In Playable Area";
            this.inPlayableArea.UseVisualStyleBackColor = true;
            this.inPlayableArea.CheckedChanged += new System.EventHandler(this.inPlayableArea_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.domainUpDown1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.materialName);
            this.groupBox1.Location = new System.Drawing.Point(318, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(300, 306);
            this.groupBox1.TabIndex = 25;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "General Properties";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(152, 252);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 13);
            this.label3.TabIndex = 26;
            this.label3.Text = "Material Name";
            // 
            // domainUpDown1
            // 
            this.domainUpDown1.Location = new System.Drawing.Point(155, 268);
            this.domainUpDown1.Name = "domainUpDown1";
            this.domainUpDown1.Size = new System.Drawing.Size(153, 20);
            this.domainUpDown1.TabIndex = 25;
            this.domainUpDown1.Text = "domainUpDown1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.trackBar2);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.trackBar1);
            this.groupBox2.Controls.Add(this.transparencySlider);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.isTransparent);
            this.groupBox2.Location = new System.Drawing.Point(12, 318);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(300, 345);
            this.groupBox2.TabIndex = 27;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Material Properties";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(272, 20);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(22, 13);
            this.label5.TabIndex = 24;
            this.label5.Text = "0.0";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 87);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 13);
            this.label4.TabIndex = 22;
            this.label4.Text = "Specular Exponent";
            // 
            // trackBar2
            // 
            this.trackBar2.LargeChange = 1;
            this.trackBar2.Location = new System.Drawing.Point(9, 106);
            this.trackBar2.Name = "trackBar2";
            this.trackBar2.Size = new System.Drawing.Size(285, 45);
            this.trackBar2.TabIndex = 23;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 20);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(97, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Specular Exponent";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(504, 669);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(116, 31);
            this.button1.TabIndex = 21;
            this.button1.Text = "Save";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // trackBar1
            // 
            this.trackBar1.LargeChange = 1;
            this.trackBar1.Location = new System.Drawing.Point(9, 39);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(285, 45);
            this.trackBar1.TabIndex = 20;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.emissiveColourBrowse);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.emissiveColour);
            this.groupBox3.Controls.Add(this.specularColourBrowse);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.specularColour);
            this.groupBox3.Controls.Add(this.ambientColourBrowse);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.ambientColour);
            this.groupBox3.Controls.Add(this.diffuseColourBrowse);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.diffuseColour);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.normalMapBrowse);
            this.groupBox3.Controls.Add(this.normalMap);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.specularMapBrowse);
            this.groupBox3.Controls.Add(this.specularMap);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.ambientMapBrowse);
            this.groupBox3.Controls.Add(this.ambientMap);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.diffuseMapBrowse);
            this.groupBox3.Controls.Add(this.diffuseMap);
            this.groupBox3.Location = new System.Drawing.Point(318, 318);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(300, 345);
            this.groupBox3.TabIndex = 28;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Material Maps";
            // 
            // diffuseMapBrowse
            // 
            this.diffuseMapBrowse.Location = new System.Drawing.Point(219, 35);
            this.diffuseMapBrowse.Name = "diffuseMapBrowse";
            this.diffuseMapBrowse.Size = new System.Drawing.Size(75, 22);
            this.diffuseMapBrowse.TabIndex = 21;
            this.diffuseMapBrowse.Text = "Browse";
            this.diffuseMapBrowse.UseVisualStyleBackColor = true;
            this.diffuseMapBrowse.Click += new System.EventHandler(this.diffuseMapBrowse_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 20);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 13);
            this.label7.TabIndex = 27;
            this.label7.Text = "Diffuse Map";
            // 
            // diffuseMap
            // 
            this.diffuseMap.Location = new System.Drawing.Point(9, 36);
            this.diffuseMap.Name = "diffuseMap";
            this.diffuseMap.ReadOnly = true;
            this.diffuseMap.Size = new System.Drawing.Size(204, 20);
            this.diffuseMap.TabIndex = 28;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 100);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 13);
            this.label8.TabIndex = 30;
            this.label8.Text = "Ambient Map";
            // 
            // ambientMapBrowse
            // 
            this.ambientMapBrowse.Location = new System.Drawing.Point(219, 115);
            this.ambientMapBrowse.Name = "ambientMapBrowse";
            this.ambientMapBrowse.Size = new System.Drawing.Size(75, 22);
            this.ambientMapBrowse.TabIndex = 29;
            this.ambientMapBrowse.Text = "Browse";
            this.ambientMapBrowse.UseVisualStyleBackColor = true;
            this.ambientMapBrowse.Click += new System.EventHandler(this.ambientMapBrowse_Click);
            // 
            // ambientMap
            // 
            this.ambientMap.Location = new System.Drawing.Point(9, 116);
            this.ambientMap.Name = "ambientMap";
            this.ambientMap.ReadOnly = true;
            this.ambientMap.Size = new System.Drawing.Size(204, 20);
            this.ambientMap.TabIndex = 31;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 180);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(73, 13);
            this.label9.TabIndex = 33;
            this.label9.Text = "Specular Map";
            // 
            // specularMapBrowse
            // 
            this.specularMapBrowse.Location = new System.Drawing.Point(219, 195);
            this.specularMapBrowse.Name = "specularMapBrowse";
            this.specularMapBrowse.Size = new System.Drawing.Size(75, 22);
            this.specularMapBrowse.TabIndex = 32;
            this.specularMapBrowse.Text = "Browse";
            this.specularMapBrowse.UseVisualStyleBackColor = true;
            this.specularMapBrowse.Click += new System.EventHandler(this.specularMapBrowse_Click);
            // 
            // specularMap
            // 
            this.specularMap.Location = new System.Drawing.Point(9, 196);
            this.specularMap.Name = "specularMap";
            this.specularMap.ReadOnly = true;
            this.specularMap.Size = new System.Drawing.Size(204, 20);
            this.specularMap.TabIndex = 34;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 260);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(64, 13);
            this.label10.TabIndex = 36;
            this.label10.Text = "Normal Map";
            // 
            // normalMapBrowse
            // 
            this.normalMapBrowse.Location = new System.Drawing.Point(219, 275);
            this.normalMapBrowse.Name = "normalMapBrowse";
            this.normalMapBrowse.Size = new System.Drawing.Size(75, 22);
            this.normalMapBrowse.TabIndex = 35;
            this.normalMapBrowse.Text = "Browse";
            this.normalMapBrowse.UseVisualStyleBackColor = true;
            this.normalMapBrowse.Click += new System.EventHandler(this.normalMapBrowse_Click);
            // 
            // normalMap
            // 
            this.normalMap.Location = new System.Drawing.Point(9, 276);
            this.normalMap.Name = "normalMap";
            this.normalMap.ReadOnly = true;
            this.normalMap.Size = new System.Drawing.Size(204, 20);
            this.normalMap.TabIndex = 37;
            // 
            // diffuseColour
            // 
            this.diffuseColour.Location = new System.Drawing.Point(9, 75);
            this.diffuseColour.Name = "diffuseColour";
            this.diffuseColour.Size = new System.Drawing.Size(204, 22);
            this.diffuseColour.TabIndex = 38;
            this.diffuseColour.TabStop = false;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 59);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(73, 13);
            this.label11.TabIndex = 39;
            this.label11.Text = "Diffuse Colour";
            // 
            // diffuseColourBrowse
            // 
            this.diffuseColourBrowse.Location = new System.Drawing.Point(219, 75);
            this.diffuseColourBrowse.Name = "diffuseColourBrowse";
            this.diffuseColourBrowse.Size = new System.Drawing.Size(75, 22);
            this.diffuseColourBrowse.TabIndex = 40;
            this.diffuseColourBrowse.Text = "Browse";
            this.diffuseColourBrowse.UseVisualStyleBackColor = true;
            this.diffuseColourBrowse.Click += new System.EventHandler(this.diffuseColourBrowse_Click);
            // 
            // ambientColourBrowse
            // 
            this.ambientColourBrowse.Location = new System.Drawing.Point(219, 155);
            this.ambientColourBrowse.Name = "ambientColourBrowse";
            this.ambientColourBrowse.Size = new System.Drawing.Size(75, 22);
            this.ambientColourBrowse.TabIndex = 43;
            this.ambientColourBrowse.Text = "Browse";
            this.ambientColourBrowse.UseVisualStyleBackColor = true;
            this.ambientColourBrowse.Click += new System.EventHandler(this.ambientColourBrowse_Click);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 139);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(78, 13);
            this.label12.TabIndex = 42;
            this.label12.Text = "Ambient Colour";
            // 
            // ambientColour
            // 
            this.ambientColour.Location = new System.Drawing.Point(9, 155);
            this.ambientColour.Name = "ambientColour";
            this.ambientColour.Size = new System.Drawing.Size(204, 22);
            this.ambientColour.TabIndex = 41;
            this.ambientColour.TabStop = false;
            // 
            // specularColourBrowse
            // 
            this.specularColourBrowse.Location = new System.Drawing.Point(219, 235);
            this.specularColourBrowse.Name = "specularColourBrowse";
            this.specularColourBrowse.Size = new System.Drawing.Size(75, 22);
            this.specularColourBrowse.TabIndex = 46;
            this.specularColourBrowse.Text = "Browse";
            this.specularColourBrowse.UseVisualStyleBackColor = true;
            this.specularColourBrowse.Click += new System.EventHandler(this.specularColourBrowse_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 219);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(82, 13);
            this.label13.TabIndex = 45;
            this.label13.Text = "Specular Colour";
            // 
            // specularColour
            // 
            this.specularColour.Location = new System.Drawing.Point(9, 235);
            this.specularColour.Name = "specularColour";
            this.specularColour.Size = new System.Drawing.Size(204, 22);
            this.specularColour.TabIndex = 44;
            this.specularColour.TabStop = false;
            // 
            // emissiveColourBrowse
            // 
            this.emissiveColourBrowse.Location = new System.Drawing.Point(219, 315);
            this.emissiveColourBrowse.Name = "emissiveColourBrowse";
            this.emissiveColourBrowse.Size = new System.Drawing.Size(75, 22);
            this.emissiveColourBrowse.TabIndex = 49;
            this.emissiveColourBrowse.Text = "Browse";
            this.emissiveColourBrowse.UseVisualStyleBackColor = true;
            this.emissiveColourBrowse.Click += new System.EventHandler(this.emissiveColourBrowse_Click);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 299);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(81, 13);
            this.label14.TabIndex = 48;
            this.label14.Text = "Emissive Colour";
            // 
            // emissiveColour
            // 
            this.emissiveColour.Location = new System.Drawing.Point(9, 315);
            this.emissiveColour.Name = "emissiveColour";
            this.emissiveColour.Size = new System.Drawing.Size(204, 22);
            this.emissiveColour.TabIndex = 47;
            this.emissiveColour.TabStop = false;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(272, 87);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(22, 13);
            this.label15.TabIndex = 25;
            this.label15.Text = "0.0";
            this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.label15.Click += new System.EventHandler(this.label15_Click);
            // 
            // onTrack
            // 
            this.onTrack.AutoSize = true;
            this.onTrack.Location = new System.Drawing.Point(6, 42);
            this.onTrack.Name = "onTrack";
            this.onTrack.Size = new System.Drawing.Size(139, 17);
            this.onTrack.TabIndex = 27;
            this.onTrack.TabStop = true;
            this.onTrack.Text = "Standard Track Surface";
            this.onTrack.UseVisualStyleBackColor = true;
            // 
            // offTrack
            // 
            this.offTrack.AutoSize = true;
            this.offTrack.Location = new System.Drawing.Point(6, 65);
            this.offTrack.Name = "offTrack";
            this.offTrack.Size = new System.Drawing.Size(110, 17);
            this.offTrack.TabIndex = 28;
            this.offTrack.TabStop = true;
            this.offTrack.Text = "Off-Track Surface";
            this.offTrack.UseVisualStyleBackColor = true;
            // 
            // boostPad
            // 
            this.boostPad.AutoSize = true;
            this.boostPad.Location = new System.Drawing.Point(6, 88);
            this.boostPad.Name = "boostPad";
            this.boostPad.Size = new System.Drawing.Size(74, 17);
            this.boostPad.TabIndex = 29;
            this.boostPad.TabStop = true;
            this.boostPad.Text = "Boost Pad";
            this.boostPad.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.inPlayableArea);
            this.groupBox4.Controls.Add(this.boostPad);
            this.groupBox4.Controls.Add(this.onTrack);
            this.groupBox4.Controls.Add(this.offTrack);
            this.groupBox4.Location = new System.Drawing.Point(9, 62);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(285, 112);
            this.groupBox4.TabIndex = 30;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Collision Config";
            // 
            // Model_Importer_MaterialEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(627, 707);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.materialPreview);
            this.Controls.Add(this.button1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Model_Importer_MaterialEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Material Editor";
            this.Load += new System.EventHandler(this.Model_Importer_MaterialEditor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.materialPreview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.transparencySlider)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.diffuseColour)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ambientColour)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.specularColour)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emissiveColour)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox materialPreview;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox materialName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox isTransparent;
        private System.Windows.Forms.TrackBar transparencySlider;
        private System.Windows.Forms.CheckBox inPlayableArea;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DomainUpDown domainUpDown1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trackBar2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button emissiveColourBrowse;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.PictureBox emissiveColour;
        private System.Windows.Forms.Button specularColourBrowse;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.PictureBox specularColour;
        private System.Windows.Forms.Button ambientColourBrowse;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.PictureBox ambientColour;
        private System.Windows.Forms.Button diffuseColourBrowse;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.PictureBox diffuseColour;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button normalMapBrowse;
        private System.Windows.Forms.TextBox normalMap;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button specularMapBrowse;
        private System.Windows.Forms.TextBox specularMap;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button ambientMapBrowse;
        private System.Windows.Forms.TextBox ambientMap;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button diffuseMapBrowse;
        private System.Windows.Forms.TextBox diffuseMap;
        private System.Windows.Forms.RadioButton boostPad;
        private System.Windows.Forms.RadioButton offTrack;
        private System.Windows.Forms.RadioButton onTrack;
        private System.Windows.Forms.GroupBox groupBox4;
    }
}