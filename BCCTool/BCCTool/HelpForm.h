#pragma once

namespace BCCTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ HelpForm
	/// </summary>
	public ref class HelpForm : public System::Windows::Forms::Form
	{
	public:
		HelpForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~HelpForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listBox1;
	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(25) {
				L" Beetle Crazy Cup Tool v1.6 by JaKeN525", L"",
					L"Controls:", L"WASD - model rotation.", L"QE - decrease/increase the object.", L"", L"Description:", L"- dat unpacker. Unpack all files in the archives: 3d, artwork, wave and menus.",
					L"", L" - dat packer. Creates a new archive based on the received data. If one", L" of the folders does not exist, then the archive will not be",
					L" created. It is advisable to delete unnecessary files that", L" should not be in the archive.", L"", L" - obj2inf. Converter of 3d models from wavefront obj files to inf, ver,",
					L" tri and nor. Textures should have a color depth of 8 bits with a resolution of 7"
					L"2", L" dpi in bmp format (for software render mode). The convertible model must",
					L" be adjusted in size. Automatic texture selection mode, gets the texture", L" number due to the name of the material that should be superimposed on a",
					L" PART of the 3d model.  Large models should not consist of a single material", L" (this crushes the game).", L"", L" - inf2obj. Converter of 3d models from inf, ver, tri files to wavefront obj. Now"
					L" it",
					L" converts along with the material that has the texture number in its name.", L" Made by mariokart64n (coreynguyen)."
			});
			this->listBox1->Location = System::Drawing::Point(13, 13);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(478, 292);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &HelpForm::listBox1_SelectedIndexChanged);
			// 
			// HelpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(503, 319);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"HelpForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Help";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
