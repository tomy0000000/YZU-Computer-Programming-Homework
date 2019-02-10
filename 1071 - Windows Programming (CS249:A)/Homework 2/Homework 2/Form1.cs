using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework_2
{
    public partial class Form1 : Form
    {
        List<List<int>> board = new List<List<int>>();
        List<Point[]> end_lines = new List<Point[]>();
        public Form1()
        {
            InitializeComponent();
        }

        private void Game_Init()
        {
            board.Clear();
            for (int i = 0; i < 3; i++)
            {
                board.Add(new List<int>());
                for (int j = 0; j < 3; j++)
                {
                    board[i].Add(0);
                }
            }
            end_lines.Clear();
            this.Invalidate();
            label1.Text = "Your Turn!";
        }

        private bool Game_End()
        {
            bool result = false;
            for (int i = 0; i < 3; i++)
            {
                // Check rows
                if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == board[i][2])
                {
                    Point[] tmp = new Point[2];
                    tmp[0].X = 30;
                    tmp[0].Y = i * 60 + 55;
                    tmp[1].X = 150;
                    tmp[1].Y = i * 60 + 55;
                    end_lines.Add(tmp);
                    if (board[i][0] == 1)
                    {
                        label1.Text = "You Win!";
                    }
                    else
                    {
                        label1.Text = "You Lose!";
                    }
                    result = true;
                }
                // Check cols
                if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == board[2][i])
                {
                    Point[] tmp = new Point[2];
                    tmp[0].X = i * 60 + 30;
                    tmp[0].Y = 55;
                    tmp[1].X = i * 60 + 30;
                    tmp[1].Y = 175;
                    end_lines.Add(tmp);
                    if (board[0][i] == 1)
                    {
                        label1.Text = "You Win!";
                    }
                    else
                    {
                        label1.Text = "You Lose!";
                    }
                    result = true;
                }
            }
            // Check Tilt 1
            if (board[0][0] != 0 && board[0][0] == board[1][1]&& board[1][1] == board[2][2] && board[0][0] == board[2][2])
            {
                Point[] tmp = new Point[2];
                tmp[0].X = 30;
                tmp[0].Y = 55;
                tmp[1].X = 150;
                tmp[1].Y = 175;
                end_lines.Add(tmp);
                if (board[0][0] == 1)
                {
                    label1.Text = "You Win!";
                }
                else
                {
                    label1.Text = "You Lose!";
                }
                result = true;
            }
            // Check Tilt 2
            if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == board[2][0])
            {
                Point[] tmp = new Point[2];
                tmp[0].X = 150;
                tmp[0].Y = 55;
                tmp[1].X = 30;
                tmp[1].Y = 175;
                end_lines.Add(tmp);
                if (board[0][2] == 1)
                {
                    label1.Text = "You Win!";
                }
                else
                {
                    label1.Text = "You Lose!";
                }
                result = true;
            }
            // Check All Filled
            bool all_filled = true;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == 0)
                    {
                        all_filled = false;
                        break;
                    }
                }
                if (!all_filled)
                {
                    break;
                }
            }
            if (all_filled)
            {
                label1.Text = "It's a Tie!";
                result = true;
            }
            return result;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Game_Init();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // Draw Grid
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    Pen grid_pen = new Pen(Color.Black, 3);
                    Rectangle rect = new Rectangle(i*60, j*60 + 25, 60, 60); // 寬高100的矩形區域
                    e.Graphics.DrawRectangle(grid_pen, rect); // 繪出矩形
                }
            }

            // Draw Circle and Cross
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == 1)
                    {
                        Pen grf_pen = new Pen(Color.Blue, 3);
                        e.Graphics.DrawEllipse(grf_pen, j * 60 + 5, i * 60 + 30, 50, 50);
                    }
                    else if (board[i][j] == 2)
                    {
                        Pen grf_pen = new Pen(Color.Blue, 3);
                        e.Graphics.DrawLine(grf_pen, j * 60 + 5, i * 60 + 30, j * 60 + 55, i * 60 + 80);
                        e.Graphics.DrawLine(grf_pen, j * 60 + 55, i * 60 + 30, j * 60 + 5, i * 60 + 80);
                    }
                }
            }

            // Draw Results if Game Ends
            if (Game_End())
            {
                Pen res_pen = new Pen(Color.Red, 3);
                for (int i = 0; i < end_lines.Count(); i++)
                {
                    e.Graphics.DrawLines(res_pen, end_lines[i]);
                }
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            if (Game_End())
            {
                return;
            }
            int col;
            if (0 < e.X && e.X < 60)
            {
                col = 0;
            }
            else if (60 < e.X && e.X < 120)
            {
                col = 1;
            }
            else if (120 < e.X && e.X < 180)
            {
                col = 2;
            }
            else
            {
                return;
            }

            int row;
            if (25 < e.Y && e.Y < 85)
            {
                row = 0;
            }
            else if (85 < e.Y && e.Y < 145)
            {
                row = 1;
            }
            else if (145 < e.Y && e.Y < 205)
            {
                row = 2;
            }
            else
            {
                return;
            }

            if (board[row][col] != 0)
            {
                label1.Text = "Pick Another Spot";
                return;
            }
            board[row][col] = 1;
            this.Invalidate();

            if (Game_End())
            {
                this.Invalidate();
                return;
            }

            // Computer Random Pick a spot
            Random rd = new Random();
            int comp_row = rd.Next(3);
            int comp_col = rd.Next(3);
            while (board[comp_row][comp_col] != 0)
            {
                comp_row = rd.Next(3);
                comp_col = rd.Next(3);
            }
            board[comp_row][comp_col] = 2;
            this.Invalidate();
            label1.Text = "Your Turn!";
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Game_Init();
        }
    }
}
