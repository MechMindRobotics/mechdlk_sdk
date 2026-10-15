
namespace Mmind.Dl.Examples
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.select_model = new System.Windows.Forms.Button();
            this.select_picture = new System.Windows.Forms.Button();
            this.get_result = new System.Windows.Forms.Button();
            this.Ori_picture = new System.Windows.Forms.Panel();
            this.infer_picture = new System.Windows.Forms.Panel();
            this.model_name = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // select_model
            // 
            this.select_model.Location = new System.Drawing.Point(591, 1015);
            this.select_model.Name = "select_model";
            this.select_model.Size = new System.Drawing.Size(150, 80);
            this.select_model.TabIndex = 0;
            this.select_model.Text = "选择模型";
            this.select_model.UseVisualStyleBackColor = true;
            this.select_model.Click += new System.EventHandler(this.select_model_Click);
            // 
            // select_picture
            // 
            this.select_picture.Location = new System.Drawing.Point(1004, 1015);
            this.select_picture.Name = "select_picture";
            this.select_picture.Size = new System.Drawing.Size(150, 80);
            this.select_picture.TabIndex = 1;
            this.select_picture.Text = "选择图片";
            this.select_picture.UseVisualStyleBackColor = true;
            this.select_picture.Click += new System.EventHandler(this.select_picture_Click);
            // 
            // get_result
            // 
            this.get_result.Location = new System.Drawing.Point(1406, 1015);
            this.get_result.Name = "get_result";
            this.get_result.Size = new System.Drawing.Size(150, 80);
            this.get_result.TabIndex = 2;
            this.get_result.Text = "运行";
            this.get_result.UseVisualStyleBackColor = true;
            this.get_result.Click += new System.EventHandler(this.get_result_Click);
            // 
            // Ori_picture
            // 
            this.Ori_picture.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Ori_picture.Location = new System.Drawing.Point(53, 61);
            this.Ori_picture.Name = "Ori_picture";
            this.Ori_picture.Size = new System.Drawing.Size(900, 900);
            this.Ori_picture.TabIndex = 3;
            // 
            // infer_picture
            // 
            this.infer_picture.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.infer_picture.Location = new System.Drawing.Point(1230, 61);
            this.infer_picture.Name = "infer_picture";
            this.infer_picture.Size = new System.Drawing.Size(900, 900);
            this.infer_picture.TabIndex = 4;
            // 
            // model_name
            // 
            this.model_name.Location = new System.Drawing.Point(959, 481);
            this.model_name.Name = "model_name";
            this.model_name.ReadOnly = true;
            this.model_name.Size = new System.Drawing.Size(265, 25);
            this.model_name.TabIndex = 5;
            this.model_name.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(2282, 1153);
            this.Controls.Add(this.model_name);
            this.Controls.Add(this.infer_picture);
            this.Controls.Add(this.Ori_picture);
            this.Controls.Add(this.get_result);
            this.Controls.Add(this.select_picture);
            this.Controls.Add(this.select_model);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button select_model;
        private System.Windows.Forms.Button select_picture;
        private System.Windows.Forms.Button get_result;
        private System.Windows.Forms.Panel Ori_picture;
        private System.Windows.Forms.Panel infer_picture;
        private System.Windows.Forms.TextBox model_name;
    }
}

