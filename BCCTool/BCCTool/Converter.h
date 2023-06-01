#pragma once
#include "Undat.h"

namespace BCCTool 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	public ref class Converter : public System::Windows::Forms::Form
	{
	public:
		bool isUnpack;
		bool isUnpacking = false;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;

	public:
		std::string* path;

		Converter(std::string path)
		{
			InitializeComponent();
			this->path = new std::string{ path };
		}

	protected:
		~Converter()
		{
			delete path;
			if (components)
				delete components;
		}

	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::CheckBox^ checkBox6;
	private: System::Windows::Forms::CheckBox^ checkBox5;


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox4);
			this->groupBox1->Controls->Add(this->checkBox3);
			this->groupBox1->Controls->Add(this->checkBox2);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Location = System::Drawing::Point(13, 13);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(237, 116);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Working archives";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Location = System::Drawing::Point(7, 89);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(57, 17);
			this->checkBox4->TabIndex = 3;
			this->checkBox4->Text = L"menus";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Checked = true;
			this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox3->Location = System::Drawing::Point(7, 66);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(52, 17);
			this->checkBox3->TabIndex = 2;
			this->checkBox3->Text = L"wave";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(7, 43);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(61, 17);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = L"artwork";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(7, 20);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(38, 17);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"3d";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBox6);
			this->groupBox2->Controls->Add(this->checkBox5);
			this->groupBox2->Location = System::Drawing::Point(13, 135);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(237, 68);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Options";
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Checked = true;
			this->checkBox6->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox6->Location = System::Drawing::Point(7, 42);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(139, 17);
			this->checkBox6->TabIndex = 5;
			this->checkBox6->Text = L"Change the start screen";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Checked = true;
			this->checkBox5->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox5->Location = System::Drawing::Point(7, 19);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(156, 17);
			this->checkBox5->TabIndex = 4;
			this->checkBox5->Text = L"Create backups of archives";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(189, 222);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(61, 31);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Converter::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Converter::timer1_Tick);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Converter::backgroundWorker1_DoWork);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 206);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 6;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(13, 222);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(170, 30);
			this->progressBar1->TabIndex = 7;
			// 
			// Converter
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(262, 265);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Converter";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Archive";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Converter::Form1_FormClosing);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		isUnpacking = true;

		backgroundWorker1->RunWorkerAsync();
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		if (isUnpack)
		{
			this->Text = L"Unpacker";
			groupBox2->Enabled = false;
		}
		else
		{
			this->Text = L"Packer";
			groupBox2->Enabled = true;
		}

		if (isUnpacking)
		{
			button1->Enabled = false;
			groupBox1->Enabled = false;
		}
		else
		{
			button1->Enabled = true;
			groupBox1->Enabled = true;
		}
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
	{
		std::vector<std::string> names;

		if (checkBox1->Checked)
			names.push_back("3d");
		if (checkBox2->Checked)
			names.push_back("artwork");
		if (checkBox3->Checked)
			names.push_back("wave");
		if (checkBox4->Checked)
			names.push_back("menus");

		if (isUnpack)
			for (int i = 0; i < names.size(); i++)
			{
				System::String^ str = gcnew String(names[i].c_str());

				Unpacker archive;
				archive.SetPath(*path);

				label1->Text = L"Unpacking " + str + L".dat archive.";
				archive.Extract(names[i]);
			}
		else
			if (names.size() > 0)
				for (int i = 0; i < names.size(); i++)
				{
					System::String^ str = gcnew String(names[i].c_str());

					Unpacker archive;
					archive.SetPath(*path);

					if (checkBox5->Enabled)
						archive.createBackup = checkBox5->Checked;
					if (checkBox6->Enabled)
						archive.changeStartScreen = checkBox6->Checked;

					label1->Text = L"Packing " + str + L".dat archive.";
					archive.PackBack(names[i]);
				}

		label1->Text = L"Done!";

		isUnpacking = false;
	}

	private: void Form1_FormClosing(Object^ sender, FormClosingEventArgs^ e)
	{
		if (isUnpacking)
		{
			auto msg = MessageBox::Show("Wait for the process to finish.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Question);

			if (msg == System::Windows::Forms::DialogResult::OK)
				e->Cancel = true;
		}
	}

	private: System::Void backgroundWorker2_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		while (true)
		{

		}
	}
};
}
