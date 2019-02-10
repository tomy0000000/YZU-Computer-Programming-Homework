using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework_4
{
    public partial class Form1 : Form
    {
        Color ball_color = Color.Red;
        RectangleF square, ball, box;
        int time, ball_direction;
        float ball_speed, box_speed;
        bool left_down, right_down;

        private void Game_Init()
        {
            square = new RectangleF(0, 50, 500, 400);
            ball = new RectangleF(square.Location.X, square.Location.Y, 10, 10);
            box = new RectangleF(square.Location.X, square.Height + square.Location.Y, 40, 10);
            time = 0;
            ball_speed = 1.5f;
            box_speed = 2.0f;
            ball_direction = 4;
            left_down = false;
            right_down = false;
            timer1.Enabled = true;
            timer1.Start();
            timer2.Enabled = true;
            timer2.Start();
            timer3.Enabled = true;
            timer3.Start();
            toolStripStatusLabel2.Text = "Playing!";
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Game_Init();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Black, square.Location.X, square.Location.Y, square.Width, square.Height); // Draw Square
            Brush ball_brush = new SolidBrush(ball_color);
            e.Graphics.FillEllipse(ball_brush, ball); // Draw Ball

            Brush box_brush = new SolidBrush(Color.Red);
            e.Graphics.FillRectangle(box_brush, box); // Draw Box
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Left)
            {
                left_down = true;
            }
            else if (e.KeyData == Keys.Right)
            {
                right_down = true;
            }
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Left)
            {
                left_down = false;
            }
            else if (e.KeyData == Keys.Right)
            {
                right_down = false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (ball.Location.Y + ball.Height >= square.Location.Y + square.Height) // Floor
            {
                if (box.Location.X - ball.Width/2 <= ball.Location.X && ball.Location.X <= box.Location.X + box.Width + ball.Width / 2)
                {
                    switch (ball_direction)
                    {
                        case 3:
                            ball_direction = 2;
                            break;
                        case 4:
                            ball_direction = 1;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    toolStripStatusLabel2.Text = "Game Over!";
                    timer1.Stop();
                    timer1.Enabled = false;
                    timer2.Stop();
                    timer2.Enabled = false;
                    timer3.Stop();
                    timer3.Enabled = false;
                }
            }
            else if (ball.Location.X + ball.Width >= square.Width) // Right Wall
            {
                switch (ball_direction)
                {
                    case 1:
                        ball_direction = 2;
                        break;
                    case 4:
                        ball_direction = 3;
                        break;
                    default:
                        break;
                }
            }
            else if (ball.Location.Y <= square.Location.Y) // Ceiling
            {
                switch (ball_direction)
                {
                    case 1:
                        ball_direction = 4;
                        break;
                    case 2:
                        ball_direction = 3;
                        break;
                    default:
                        break;
                }
            }
            else if (ball.Location.X <= square.Location.X) // Left Wall
            {
                switch (ball_direction)
                {
                    case 2:
                        ball_direction = 1;
                        break;
                    case 3:
                        ball_direction = 4;
                        break;
                    default:
                        break;
                }
            }

            // Move
            switch (ball_direction)
            {
                case 1:
                    ball.Location = new PointF(ball.Location.X + ball_speed, ball.Location.Y - ball_speed);
                    break;
                case 2:
                    ball.Location = new PointF(ball.Location.X - ball_speed, ball.Location.Y - ball_speed);
                    break;
                case 3:
                    ball.Location = new PointF(ball.Location.X - ball_speed, ball.Location.Y + ball_speed);
                    break;
                case 4:
                    ball.Location = new PointF(ball.Location.X + ball_speed, ball.Location.Y + ball_speed);
                    break;
                default:
                    break;
            }
            this.Invalidate();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (left_down)
            {
                if (box.Location.X <= 0) return;
                box.Location = new PointF(box.Location.X - box_speed, box.Location.Y);
            }
            if (right_down)
            {
                if (box.Location.X >= square.Width - box.Width) return;
                box.Location = new PointF(box.Location.X + box_speed, box.Location.Y);
            }
            this.Invalidate();
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Location.X < square.Width - box.Width)
            {
                box.Location = new PointF(e.Location.X, box.Location.Y);
            }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            time++;
            toolStripStatusLabel1.Text = time.ToString();
            if (time % 5 == 0)
            {
                ball_speed *= 1.1f;
                box_speed = ball_speed + 0.5f;
            }
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Game_Init();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            ball_color = Color.Red;
            this.Invalidate();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            ball_color = Color.Green;
            this.Invalidate();
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            ball_color = Color.Blue;
            this.Invalidate();
        }
    }
}
