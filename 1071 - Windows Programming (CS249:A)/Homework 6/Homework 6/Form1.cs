using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace Homework_6
{
    public partial class Form1 : Form
    {
        int time, received, backInd;
        List<Image> Background = new List<Image>();
        List<Image> Fruits = new List<Image>();
        List<RectangleF> Fruits_boxes = new List<RectangleF>();
        List<float> Fruits_speeds = new List<float>();
        RectangleF bowl = new RectangleF(0, 0, Properties.Resources.Bowl.Width, Properties.Resources.Bowl.Height);
        ImageAttributes transparant = new ImageAttributes();
        Random random = new Random();
        bool game;

        public Form1()
        {
            InitializeComponent();

            Background.Add(Properties.Resources.Chrysanthemum);
            Background.Add(Properties.Resources.Desert);
            Background.Add(Properties.Resources.Hydrangeas);
            Background.Add(Properties.Resources.Jellyfisha);
            Background.Add(Properties.Resources.Koala);
            Background.Add(Properties.Resources.Lighthouse);
            Background.Add(Properties.Resources.Penguins);
            Background.Add(Properties.Resources.Tulips);
            float[][] transArray = {
                new float[]{1, 0, 0, 0, 0},
                new float[]{0, 1, 0, 0, 0},
                new float[]{0, 0, 1, 0, 0},
                new float[]{0, 0, 0, 0.5f, 0},
                new float[]{0, 0, 0, 0, 1}
            };
            ColorMatrix transMatrix = new ColorMatrix(transArray);
            transparant.SetColorMatrix(transMatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);
            
            Fruits.Add(Properties.Resources.Banana);
            Fruits.Add(Properties.Resources.Tomato);
            Fruits.Add(Properties.Resources.StawBerry);
            for (int i = 0; i < Fruits.Count(); i++)
            {
                Fruits_boxes.Add(new RectangleF(0, 0, Fruits[i].Width, Fruits[i].Height));
            }
        }

        void Game_Init()
        {
            time = 120;
            timer1.Enabled = true;
            timer1.Start();
            timer2.Enabled = true;
            timer2.Start();
            received = 0;
            backInd = 0;
            bowl.Y = ClientSize.Height * 0.8f;
            Fruits_speeds.Clear();
            for (int i = 0; i < Fruits.Count(); i++)
            {
                PointF fruit_loc = new PointF(random.Next(ClientSize.Width - (int)Fruits_boxes[i].Width), 0);
                Fruits_boxes[i] = new RectangleF(fruit_loc, Fruits_boxes[i].Size);
                Fruits_speeds.Add(1 + (float)random.Next(10) / 10);
            }
            game = true;
            Refresh_Panel();
            this.Invalidate();
        }

        void Game_End()
        {
            game = false;
            timer1.Stop();
            timer1.Enabled = false;
            timer2.Stop();
            timer2.Enabled = false;
            this.Invalidate();
        }

        void Refresh_Panel()
        {
            label1.Text = "Remaining: " + time + " seconds";
            label1.Text += "\nReceived: " + received;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // Time Counter
            time--;
            if (time == 0)
            {
                Game_End();
            }
            if (time % 10 == 0)
            {
                backInd = (backInd == Background.Count() - 1) ? 0 : backInd + 1;
                this.Invalidate();
            }
            Refresh_Panel();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            // For Fruits
            for (int i = 0; i < Fruits_boxes.Count(); i++)
            {
                PointF fruit_loc = new PointF(Fruits_boxes[i].X, Fruits_boxes[i].Y + Fruits_speeds[i]);
                if (fruit_loc.Y + Fruits[i].Height >= bowl.Y)
                {
                    if (bowl.X <= fruit_loc.X && fruit_loc.X + Fruits_boxes[i].Width <= bowl.X + bowl.Width)
                    {
                        received++;
                        Refresh_Panel();
                    }
                    fruit_loc.X = random.Next(random.Next(ClientSize.Width - (int)Fruits_boxes[i].Width));
                    fruit_loc.Y = 0;
                    Fruits_speeds[i] = 1 + (float)random.Next(10) / 10;
                }
                Fruits_boxes[i] = new RectangleF(fruit_loc, Fruits_boxes[i].Size);
            }
            this.Invalidate();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Game_Init();
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Location.X < ClientSize.Width)
            {
                bowl.X = e.Location.X - (Properties.Resources.Bowl.Width / 2);
                this.Invalidate();
            }
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            bowl.Y = ClientSize.Height * 0.8f;
            this.Invalidate();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // Background
            Rectangle backRect = new Rectangle(0, 0, Background[backInd].Width, Background[backInd].Height);
            e.Graphics.DrawImage(Background[backInd], backRect, 0, 0, Background[backInd].Width, Background[backInd].Height, GraphicsUnit.Pixel, transparant);

            if (!game) return;

            // Fruits
            for (int i = 0; i < Fruits.Count(); i++)
            {
                e.Graphics.DrawImage(Fruits[i], Fruits_boxes[i]);
            }

            // Bowl
            e.Graphics.DrawImage(Properties.Resources.Bowl, bowl);
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Game_End();
            Game_Init();
        }
    }
}
