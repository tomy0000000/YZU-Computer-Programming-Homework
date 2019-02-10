using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Exercise_12_1
{
    public partial class Form3 : Form
    {
        private int a = -1, r = -1, g = -1, b = -1;
        public Form3()
        {
            InitializeComponent();
        }

        public int getA()
        {
            return a;
        }
        public int getR()
        {
            return r;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            double tmp = trackBar1.Value;
            label5.Text = string.Format("{0:0.0}", tmp / 10);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            double tmp = trackBar2.Value;
            label6.Text = string.Format("{0:0.0}", tmp / 10);
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            double tmp = trackBar3.Value;
            label7.Text = string.Format("{0:0.0}", tmp / 10);
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            double tmp = trackBar4.Value;
            label8.Text = string.Format("{0:0.0}", tmp / 10);
        }

        public int getG()
        {
            return g;
        }
        public int getB()
        {
            return b;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            r = trackBar1.Value;
            g = trackBar2.Value;
            b = trackBar3.Value;
            a = trackBar4.Value;
            this.Close();
        }
    }
}
