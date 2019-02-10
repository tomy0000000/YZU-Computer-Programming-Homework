using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework_1
{
    public partial class Form1 : Form
    {
        Random rd = new Random();  //使用亂數類別
        Brush b1, b2, b3, b4, b5, b6, b7, b8, b9;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            b1 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b2 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b3 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b4 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b5 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b6 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b7 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b8 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
            b9 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillRectangle(b1, 0, 0, 50, 50);
            e.Graphics.FillRectangle(b2, 50, 0, 50, 50);
            e.Graphics.FillRectangle(b3, 100, 0, 50, 50);
            e.Graphics.FillRectangle(b4, 0, 50, 50, 50);
            e.Graphics.FillRectangle(b5, 50, 50, 50, 50);
            e.Graphics.FillRectangle(b6, 100, 50, 50, 50);
            e.Graphics.FillRectangle(b7, 0, 100, 50, 50);
            e.Graphics.FillRectangle(b8, 50, 100, 50, 50);
            e.Graphics.FillRectangle(b9, 100, 100, 50, 50);
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (0 <= e.Location.Y && e.Location.Y <= 50)
            {
                if (0 <= e.Location.X && e.Location.X <= 50)
                {
                    b1 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (50 <= e.Location.X && e.Location.X <= 100)
                {
                    b2 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (100 <= e.Location.X && e.Location.X <= 150)
                {
                    b3 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
            }
            else if (50 <= e.Location.Y && e.Location.Y <= 100)
            {
                if (0 <= e.Location.X && e.Location.X <= 50)
                {
                    b4 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (50 <= e.Location.X && e.Location.X <= 100)
                {
                    b5 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (100 <= e.Location.X && e.Location.X <= 150)
                {
                    b6 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
            }
            else if (100 <= e.Location.Y && e.Location.Y <= 150)
            {
                if (0 <= e.Location.X && e.Location.X <= 50)
                {
                    b7 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (50 <= e.Location.X && e.Location.X <= 100)
                {
                    b8 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
                else if (100 <= e.Location.X && e.Location.X <= 150)
                {
                    b9 = new SolidBrush(Color.FromArgb(rd.Next(256), rd.Next(256), rd.Next(256)));
                }
            }
            this.Invalidate();
        }
    }
}
