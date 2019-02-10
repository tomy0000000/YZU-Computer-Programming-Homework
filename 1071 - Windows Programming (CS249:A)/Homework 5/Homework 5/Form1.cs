using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework_5
{
    public partial class Form1 : Form
    {
        List<List<int>> grid = new List<List<int>>();
        List<PictureBox> picboxes = new List<PictureBox>();
        List<PictureBox> restore_picbox = new List<PictureBox>();
        List<bool> flipped = new List<bool>();
        int time, restore_time;
        int selected_row = -1;
        int selected_col = -1;

        public Form1()
        {
            InitializeComponent();
        }

        private void Game_Init()
        {
            time = 0;
            restore_time = -1;
            selected_row = selected_col = -1;
            timer1.Enabled = true;
            timer1.Start();
            Random rd = new Random();

            flipped.Clear();
            for (int i = 0; i < 8; i++)
            {
                flipped.Add(false);
            }

            grid.Clear();
            for (int i = 0; i < 4; i++)
            {
                grid.Add(new List<int>());
            }
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    grid[i].Add(0);
                }
            }

            for (int i = 1; i <= 8; i++)
            {
                int row = rd.Next(4);
                int col = rd.Next(4);
                while (grid[row][col] != 0)
                {
                    row = rd.Next(4);
                    col = rd.Next(4);
                }
                grid[row][col] = i;
                while (grid[row][col] != 0)
                {
                    row = rd.Next(4);
                    col = rd.Next(4);
                }
                grid[row][col] = i;
            }

            for (int i = 0; i < picboxes.Count(); i++)
            {
                Show_Pic(picboxes[i], 0);
            }
        }

        private void Check_End()
        {
            for (int i = 0; i < flipped.Count(); i++)
            {
                if (!flipped[i])
                {
                    return;
                }
            }
            timer1.Stop();
            timer1.Enabled = false;
            label1.Text = time.ToString() + " Seconds: Game Over";
        }

        private void Show_Pic(PictureBox pic_box, int pic_num)
        {
            switch (pic_num)
            {
                case 0:
                    pic_box.Image = Properties.Resources._8_0;
                    break;
                case 1:
                    pic_box.Image = Properties.Resources._8_1;
                    break;
                case 2:
                    pic_box.Image = Properties.Resources._8_2;
                    break;
                case 3:
                    pic_box.Image = Properties.Resources._8_3;
                    break;
                case 4:
                    pic_box.Image = Properties.Resources._8_4;
                    break;
                case 5:
                    pic_box.Image = Properties.Resources._8_5;
                    break;
                case 6:
                    pic_box.Image = Properties.Resources._8_6;
                    break;
                case 7:
                    pic_box.Image = Properties.Resources._8_7;
                    break;
                case 8:
                    pic_box.Image = Properties.Resources._8_8;
                    break;
                default:
                    break;
            }
        }

        private void Click_action(int pic_num)
        {
            int theRow = pic_num / 4;
            int theCol = pic_num % 4;
            if (selected_row == -1 && selected_col == -1)
            {
                selected_row = theRow;
                selected_col = theCol;
                Show_Pic(picboxes[pic_num], grid[theRow][theCol]);
                restore_picbox.Add(picboxes[pic_num]);
            }
            else if (selected_row == theRow && selected_col == theCol)
            {
                return;
            }
            else if (grid[selected_row][selected_col] == grid[theRow][theCol])
            {
                Show_Pic(picboxes[pic_num], grid[theRow][theCol]);
                restore_picbox.Clear();
                selected_row = selected_col = -1;
                flipped[grid[theRow][theCol] - 1] = true;
                Check_End();
            }
            else if (grid[selected_row][selected_col] != grid[theRow][theCol])
            {
                Show_Pic(picboxes[pic_num], grid[theRow][theCol]);
                restore_picbox.Add(picboxes[pic_num]);
                restore_time = time + 1;
                selected_row = selected_col = -1;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            picboxes.Add(pictureBox1);
            picboxes.Add(pictureBox2);
            picboxes.Add(pictureBox3);
            picboxes.Add(pictureBox4);
            picboxes.Add(pictureBox5);
            picboxes.Add(pictureBox6);
            picboxes.Add(pictureBox7);
            picboxes.Add(pictureBox8);
            picboxes.Add(pictureBox9);
            picboxes.Add(pictureBox10);
            picboxes.Add(pictureBox11);
            picboxes.Add(pictureBox12);
            picboxes.Add(pictureBox13);
            picboxes.Add(pictureBox14);
            picboxes.Add(pictureBox15);
            picboxes.Add(pictureBox16);
            Game_Init();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            time++;
            label1.Text = time.ToString() + " Seconds";
            if (time == restore_time)
            {
                for (int i = 0; i < restore_picbox.Count(); i++)
                {
                    Show_Pic(restore_picbox[i], 0);
                }
                restore_picbox.Clear();
                restore_time = -1;
            }
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Game_Init();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(0);
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(1);
            }
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(2);
            }
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(3);
            }
        }

        private void pictureBox5_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(4);
            }
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(5);
            }
        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(6);
            }
        }

        private void pictureBox8_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(7);
            }
        }

        private void pictureBox9_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(8);
            }
        }

        private void pictureBox10_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(9);
            }
        }

        private void pictureBox11_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(10);
            }
        }

        private void pictureBox12_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(11);
            }
        }

        private void pictureBox13_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(12);
            }
        }

        private void pictureBox14_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(13);
            }
        }

        private void pictureBox15_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(14);
            }
        }

        private void pictureBox16_Click(object sender, EventArgs e)
        {
            if (restore_time == -1)
            {
                Click_action(15);
            }
        }
    }
}
