//---------------------------------------------------------------------------

#ifndef MyPaintH
#define MyPaintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *FrameForItems;
	TSpeedButton *line;
	TImage *WorkSpace;
	TMainMenu *Menu;
	TSpeedButton *rectangle;
	TSpeedButton *ellipse;
	TMenuItem *File;
	TMenuItem *Exit;
	TMenuItem *Clear;
	TComboBox *LineWidth;
	TLabel *LineWidthLabel;
	TColorBox *ColorLine;
	TLabel *ColorLabel;
	TComboBox *LineStyle;
	TLabel *LineStyleLabel;
	TColorBox *BrushColor;
	TLabel *BrushColorLabel;
	TComboBox *BrushStyle;
	TLabel *BrushStyleLabel;
	TSpeedButton *Eraser;
	TSpeedButton *Pen;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall ClearClick(TObject *Sender);
	void __fastcall WorkSpaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall WorkSpaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall LineWidthChange(TObject *Sender);
	void __fastcall ColorLineChange(TObject *Sender);
	void __fastcall LineStyleChange(TObject *Sender);
	void __fastcall BrushColorChange(TObject *Sender);
	void __fastcall BrushStyleChange(TObject *Sender);
	void __fastcall WorkSpaceMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
private:	// User declarations
	/*
	  ƒелаем методы рисовани€ закрытыми, так как их нельз€ просто так вз€ть и вызвать.
	  Ёто может сделать только сама мышь при манипул€ции с нею  в области действи€ холста.
	  я использую константные ссылки с целью экономии пам€ти. ¬озможно вам покажетс€
	  смешным мой аргумент, но € так привык. ћне так удобно.
	*/
	inline void WhichPrimitive(const bool & , const int & , const int &);
	inline void Erase(const int & , const int &);
	inline void PenDraw(const int & , const int &);
	inline void DrawLine(const bool & , const int & , const  int &);
	inline void DrawRectangle(const bool & , const int & , const int &);
	inline void DrawEllipse(const bool & , const int & , const int &);
	bool IsButtonPressed;
	static const short int MagicNumber = 10;    // онстанта дл€ стирани€ холста.
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
