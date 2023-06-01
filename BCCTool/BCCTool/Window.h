#pragma once

#include "obj2infConverter.h"
#include "HelpForm.h"
#include "OpenGL.h"
#include "Converter.h"
#include "mk64n.h"
#include <filesystem>
#include <windows.h>
#include <string>

namespace fs = std::filesystem;

namespace BCCTool
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenGLForm;

	public ref class Window : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Label^ label6;

	public:
		std::string* currentPath = new std::string { fs::current_path().string() };
	private: System::Windows::Forms::HScrollBar^ hScrollBar4;

	public:
		bool block = false;
		bool infBlock = false;
		inf2obj con;

	public:
		HelpForm^ formHelp = gcnew HelpForm;
		obj2infConverter^ converter = gcnew obj2infConverter(currentPath);

	private:
		System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ button5;

	public:
		Converter^ archive = gcnew Converter(*currentPath);

		Window(void)
		{
			InitializeComponent();

			con.path = currentPath;

			this->KeyDown += gcnew KeyEventHandler(this, &Window::keyBoard);
			OpenGL = gcnew COpenGL(this, 970, 555);
		}

	protected:
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ unpack;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	public:
		COpenGL^ OpenGL;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Window::typeid));
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->unpack = (gcnew System::Windows::Forms::Button());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->hScrollBar4 = (gcnew System::Windows::Forms::HScrollBar());
			   this->label10 = (gcnew System::Windows::Forms::Label());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->button5 = (gcnew System::Windows::Forms::Button());
			   this->groupBox1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->label7);
			   this->groupBox1->Controls->Add(this->button5);
			   this->groupBox1->Controls->Add(this->label5);
			   this->groupBox1->Controls->Add(this->label4);
			   this->groupBox1->Controls->Add(this->button4);
			   this->groupBox1->Controls->Add(this->button3);
			   this->groupBox1->Controls->Add(this->label3);
			   this->groupBox1->Controls->Add(this->button2);
			   this->groupBox1->Controls->Add(this->label2);
			   this->groupBox1->Controls->Add(this->button1);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->unpack);
			   this->groupBox1->Location = System::Drawing::Point(12, 2);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(970, 106);
			   this->groupBox1->TabIndex = 0;
			   this->groupBox1->TabStop = false;
			   // 
			   // label5
			   // 
			   this->label5->Location = System::Drawing::Point(392, 87);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(71, 13);
			   this->label5->TabIndex = 5;
			   this->label5->Text = L"Help";
			   this->label5->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // label4
			   // 
			   this->label4->Location = System::Drawing::Point(238, 87);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(71, 13);
			   this->label4->TabIndex = 7;
			   this->label4->Text = L"obj2inf";
			   this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // button4
			   // 
			   this->button4->AutoSize = true;
			   this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->button4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.Image")));
			   this->button4->Location = System::Drawing::Point(392, 11);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(71, 71);
			   this->button4->TabIndex = 4;
			   this->button4->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &Window::button4_Click);
			   // 
			   // button3
			   // 
			   this->button3->AutoSize = true;
			   this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			   this->button3->Location = System::Drawing::Point(238, 11);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(71, 71);
			   this->button3->TabIndex = 6;
			   this->button3->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Window::button3_Click);
			   // 
			   // label3
			   // 
			   this->label3->Location = System::Drawing::Point(161, 87);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(71, 13);
			   this->label3->TabIndex = 5;
			   this->label3->Text = L"inf2obj";
			   this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // button2
			   // 
			   this->button2->AutoSize = true;
			   this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			   this->button2->Location = System::Drawing::Point(161, 11);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(71, 71);
			   this->button2->TabIndex = 4;
			   this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Window::button2_Click);
			   // 
			   // label2
			   // 
			   this->label2->Location = System::Drawing::Point(84, 87);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(71, 13);
			   this->label2->TabIndex = 3;
			   this->label2->Text = L"Pack";
			   this->label2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // button1
			   // 
			   this->button1->AutoSize = true;
			   this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			   this->button1->Location = System::Drawing::Point(84, 11);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(71, 71);
			   this->button1->TabIndex = 2;
			   this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Window::button1_Click_1);
			   // 
			   // label1
			   // 
			   this->label1->Location = System::Drawing::Point(7, 87);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(71, 13);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"Unpack";
			   this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // unpack
			   // 
			   this->unpack->AutoSize = true;
			   this->unpack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->unpack->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"unpack.Image")));
			   this->unpack->Location = System::Drawing::Point(7, 11);
			   this->unpack->Name = L"unpack";
			   this->unpack->Size = System::Drawing::Size(71, 71);
			   this->unpack->TabIndex = 0;
			   this->unpack->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->unpack->UseVisualStyleBackColor = true;
			   this->unpack->Click += gcnew System::EventHandler(this, &Window::button1_Click);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(655, 643);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(35, 13);
			   this->label6->TabIndex = 11;
			   this->label6->Text = L"label6";
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Interval = 10;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Window::timer1_Tick);
			   // 
			   // hScrollBar4
			   // 
			   this->hScrollBar4->LargeChange = 1;
			   this->hScrollBar4->Location = System::Drawing::Point(658, 656);
			   this->hScrollBar4->Maximum = 10;
			   this->hScrollBar4->Minimum = 1;
			   this->hScrollBar4->Name = L"hScrollBar4";
			   this->hScrollBar4->Size = System::Drawing::Size(327, 17);
			   this->hScrollBar4->TabIndex = 15;
			   this->hScrollBar4->Value = 1;
			   // 
			   // label10
			   // 
			   this->label10->AutoSize = true;
			   this->label10->BackColor = System::Drawing::Color::Transparent;
			   this->label10->Location = System::Drawing::Point(621, 656);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(39, 13);
			   this->label10->TabIndex = 16;
			   this->label10->Text = L"speed:";
			   // 
			   // label7
			   // 
			   this->label7->Location = System::Drawing::Point(315, 87);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(71, 13);
			   this->label7->TabIndex = 9;
			   this->label7->Text = L"Map Editor";
			   this->label7->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			   // 
			   // button5
			   // 
			   this->button5->AutoSize = true;
			   this->button5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->button5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.Image")));
			   this->button5->Location = System::Drawing::Point(315, 11);
			   this->button5->Name = L"button5";
			   this->button5->Size = System::Drawing::Size(71, 71);
			   this->button5->TabIndex = 8;
			   this->button5->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button5->UseVisualStyleBackColor = true;
			   // 
			   // Window
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			   this->CausesValidation = false;
			   this->ClientSize = System::Drawing::Size(994, 681);
			   this->Controls->Add(this->label10);
			   this->Controls->Add(this->hScrollBar4);
			   this->Controls->Add(this->groupBox1);
			   this->Controls->Add(this->label6);
			   this->DoubleBuffered = true;
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->MaximizeBox = false;
			   this->Name = L"Window";
			   this->Text = L"Beetle Crazy Cup Tool v1.7";
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: void keyBoard(System::Object^ sender, KeyEventArgs^ e)
	{
		switch (e->KeyCode) 
		{
		case Keys::S:
			rotateY -= 0.5f * hScrollBar4->Value;
			break;

		case Keys::W:
			rotateY += 0.5f * hScrollBar4->Value;
			break;

		case Keys::D:
			rotateX -= 0.5f * hScrollBar4->Value;
			break;

		case Keys::A:
			rotateX += 0.5f * hScrollBar4->Value;
			break;

		case Keys::Q:
			if (zoom - 0.1f > 0)
				zoom -= 0.1f;
			break;

		case Keys::E:
				zoom += 0.1f;
			break;
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenGL->Reset();
		archive = gcnew Converter(*currentPath);
		archive->isUnpack = true;
		archive->Show();
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenGL->Reset();
		con.Reset();
		con.Convert();

		if (con.vertices != NULL)
		{
			OpenGL->facesNum = con.num_triangles;
			OpenGL->vertices = con.vertices;
			OpenGL->faces = con.verTri;
			OpenGL->verNum = con.num_vertices;
		}
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);

		OpenGL->Render();
		OpenGL->SwapOpenGLBuffers();

		label6->Text = L"speed: X" + hScrollBar4->Value + L" zoom: " + zoom + L" x: " + rotateX + L" y: " + rotateY;

		block = formHelp->Visible || converter->Visible || archive->Visible || con.block;

		if (block)
		{
			this->groupBox1->Enabled = false;
			this->hScrollBar4->Enabled = false;
		}
		else
		{
			this->groupBox1->Enabled = true;
			this->hScrollBar4->Enabled = true;
		}
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenGL->Reset();
		converter = gcnew obj2infConverter(currentPath);
		converter->Show();

/*		if (obj.vertices != NULL)
		{
			OpenGL->facesNum = obj.facesNum;
			OpenGL->vertices = obj.vertices;
			OpenGL->faces = obj.verTri;
			OpenGL->verNum = obj.verNum;
		}*/
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenGL->Reset();
		formHelp = gcnew HelpForm;
		formHelp->Show();
	}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e)
	{
		OpenGL->Reset();
		archive = gcnew Converter(*currentPath);
		archive->isUnpack = false;
		archive->Show();
	}
};
}
