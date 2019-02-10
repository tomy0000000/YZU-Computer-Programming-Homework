using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework_8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Refresh_Final()
        {
            int MidE, FinalE;
            int.TryParse(textBox3.Text, out MidE);
            int.TryParse(textBox4.Text, out FinalE);
            int Final = (MidE + FinalE) / 2;
            label7.Text = Final.ToString();
            pictureBox1.Visible = false;
            pictureBox2.Visible = false;
            pictureBox3.Visible = false;
            pictureBox4.Visible = false;
            if (Final >= 60)
            {
                pictureBox1.Visible = true;
            }
            if (Final >= 70)
            {
                pictureBox2.Visible = true;
            }
            if (Final >= 80)
            {
                pictureBox3.Visible = true;
            }
            if (Final >= 90)
            {
                pictureBox4.Visible = true;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: 這行程式碼會將資料載入 'studentsDataSet.Students' 資料表。您可以視需要進行移動或移除。
            this.studentsTableAdapter.Fill(this.studentsDataSet.Students);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if ((this.studentsBindingSource.Find("StudentId", textBox1.Text)) != -1)
            {
                MessageBox.Show("This ID exists!");
            }
            else
            {
                this.studentsTableAdapter.Insert(textBox1.Text, textBox2.Text, comboBox1.Text, int.Parse(textBox3.Text), int.Parse(textBox4.Text));
                this.studentsTableAdapter.Fill(this.studentsDataSet.Students);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.studentsBindingSource.EndEdit();
            this.studentsTableAdapter.Update(this.studentsDataSet);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.studentsTableAdapter.Delete(textBox1.Text, textBox2.Text, comboBox1.Text, int.Parse(textBox3.Text), int.Parse(textBox4.Text));
            this.studentsTableAdapter.Fill(this.studentsDataSet.Students);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int i = -1;
            switch (comboBox2.Text)
            {
                case "ID":
                    i = this.studentsBindingSource.Find("StudentId", textBox5.Text);
                    break;
                case "Name":
                    i = this.studentsBindingSource.Find("StudentName", textBox5.Text);
                    break;
                case "Gender":
                    i = this.studentsBindingSource.Find("Gender", textBox5.Text);
                    break;
                case "MidExam":
                    int mE;
                    if (int.TryParse(textBox5.Text, out mE))
                        i = this.studentsBindingSource.Find("MidExam", mE);
                    break;
                case "FinalExam":
                    int fE;
                    if (int.TryParse(textBox5.Text, out fE))
                        i = this.studentsBindingSource.Find("FinalExam", fE);
                    break;
            }
            if (i != -1)
                this.studentsBindingSource.Position = i;
            else
                MessageBox.Show("Not found!");
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            int val = int.Parse(textBox3.Text);
            if (val < 0 || val > 100)
            {
                MessageBox.Show("Incorrect MidExam Score!");
                textBox3.Text = "0";
            }
            else
            {
                Refresh_Final();
            }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            int val = int.Parse(textBox4.Text);
            if (val < 0 || val > 100)
            {
                MessageBox.Show("Incorrect FinalExam Score!");
                textBox4.Text = "0";
            }
            else
            {
                Refresh_Final();
            }
        }
    }
}
