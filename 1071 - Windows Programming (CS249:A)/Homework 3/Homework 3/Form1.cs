using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Drawing2D;

namespace Homework_3
{
    public partial class Form1 : Form
    {
        List<Point> startPt = new List<Point>();
        List<Point> endPt = new List<Point>();
        List<Pen> pen = new List<Pen>();
        Pen tmp = new Pen(Color.Red, 1);
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "線段檔(*.pnt)|*.pnt";
            saveFileDialog1.Filter = "線段檔(*.pnt)|*.pnt";
            tmp.DashStyle = DashStyle.Solid;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < endPt.Count(); i++)
            {
                e.Graphics.DrawLine(pen[i], startPt[i].X, startPt[i].Y, endPt[i].X, endPt[i].Y);
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            startPt.Add(e.Location);
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            endPt.Add(e.Location);
            Pen new_pen = new Pen(tmp.Color, tmp.Width);
            new_pen.DashStyle = tmp.DashStyle;
            pen.Add(new_pen);
            this.Invalidate();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                String s = saveFileDialog1.FileName;
                BinaryWriter outFile = new BinaryWriter(File.Open(s, FileMode.Create));
                outFile.Write(endPt.Count());
                for (int i = 0; i < endPt.Count(); i++)
                {
                    outFile.Write(startPt[i].X);
                    outFile.Write(startPt[i].Y);
                    outFile.Write(endPt[i].X);
                    outFile.Write(endPt[i].Y);
                    outFile.Write(pen[i].Color.ToArgb());
                    outFile.Write((int)pen[i].Width);
                    if (pen[i].DashStyle == DashStyle.Solid)
                    {
                        outFile.Write(1);
                    }
                    else if (pen[i].DashStyle == DashStyle.Dash)
                    {
                        outFile.Write(2);
                    }
                }
                outFile.Close();
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                String s = openFileDialog1.FileName;
                if (!File.Exists(s)) return;
                BinaryReader inFile = new BinaryReader(File.Open(s, FileMode.Open));
                startPt.Clear();
                endPt.Clear();
                pen.Clear();
                int n = inFile.ReadInt32();
                for (int i = 0; i < n; i++)
                {
                    startPt.Add(new Point(inFile.ReadInt32(), inFile.ReadInt32()));
                    endPt.Add(new Point(inFile.ReadInt32(), inFile.ReadInt32()));
                    Pen thePen = new Pen(Color.FromArgb(inFile.ReadInt32()), inFile.ReadInt32());
                    int PenDash = inFile.ReadInt32();
                    if (PenDash == 1)
                    {
                        thePen.DashStyle = DashStyle.Solid;
                    }
                    else if (PenDash == 2)
                    {
                        thePen.DashStyle = DashStyle.Dash;
                    }
                    pen.Add(thePen);
                }
                this.Invalidate();
                inFile.Close();
            }
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            startPt.Clear();
            endPt.Clear();
            pen.Clear();
            this.Invalidate();
        }

        private void redToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmp.Color = Color.Red;
            redToolStripMenuItem.Checked = true;
            greenToolStripMenuItem.Checked = false;
            blueToolStripMenuItem.Checked = false;
        }

        private void greenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmp.Color = Color.Green;
            redToolStripMenuItem.Checked = false;
            greenToolStripMenuItem.Checked = true;
            blueToolStripMenuItem.Checked = false;
        }

        private void blueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmp.Color = Color.Blue;
            redToolStripMenuItem.Checked = false;
            greenToolStripMenuItem.Checked = false;
            blueToolStripMenuItem.Checked = true;
        }

        private void solidToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmp.DashStyle = DashStyle.Solid;
            solidToolStripMenuItem.Checked = true;
            dashToolStripMenuItem.Checked = false;
        }

        private void dashToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmp.DashStyle = DashStyle.Dash;
            solidToolStripMenuItem.Checked = false;
            dashToolStripMenuItem.Checked = true;
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            tmp.Width = 1;
            toolStripMenuItem2.Checked = true;
            toolStripMenuItem3.Checked = false;
            toolStripMenuItem4.Checked = false;
            toolStripMenuItem5.Checked = false;
            toolStripMenuItem6.Checked = false;
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            tmp.Width = 2;
            toolStripMenuItem2.Checked = false;
            toolStripMenuItem3.Checked = true;
            toolStripMenuItem4.Checked = false;
            toolStripMenuItem5.Checked = false;
            toolStripMenuItem6.Checked = false;
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            tmp.Width = 3;
            toolStripMenuItem2.Checked = false;
            toolStripMenuItem3.Checked = false;
            toolStripMenuItem4.Checked = true;
            toolStripMenuItem5.Checked = false;
            toolStripMenuItem6.Checked = false;
        }

        private void toolStripMenuItem5_Click(object sender, EventArgs e)
        {
            tmp.Width = 4;
            toolStripMenuItem2.Checked = false;
            toolStripMenuItem3.Checked = false;
            toolStripMenuItem4.Checked = false;
            toolStripMenuItem5.Checked = true;
            toolStripMenuItem6.Checked = false;
        }

        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            tmp.Width = 5;
            toolStripMenuItem2.Checked = false;
            toolStripMenuItem3.Checked = false;
            toolStripMenuItem4.Checked = false;
            toolStripMenuItem5.Checked = false;
            toolStripMenuItem6.Checked = true;
        }
    }
}
