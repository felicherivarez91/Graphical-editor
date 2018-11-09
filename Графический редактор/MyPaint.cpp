/*
  Программа была разработана с помощью IDE Embarcadero Rad Studio 2010.
  Программа была написанна с учётом требований имплементации С++98/03 стандарта.
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "MyPaint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	IsButtonPressed = false;  //Инициализация закрытых членов данных в конструкторе
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	LineWidthChange(this);     //Задаем нашей линии значения по умолчанию.
	ColorLineChange(this);
	LineStyleChange(this);
	BrushColorChange(this);
	BrushStyleChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitClick(TObject *Sender)
{
	Application->Terminate();    //Завершение приложения
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearClick(TObject *Sender)
{
	WorkSpace->Picture = NULL;      //Очистка обьекта канвы.
	LineWidthChange(this);         //Сохраняем для нового рисунка те свойства
	ColorLineChange(this);        //которые были выставлены ранее.
	LineStyleChange(this);
	BrushColorChange(this);
	BrushStyleChange(this);
}
//---------------------------------------------------------------------------
inline void TMainForm::WhichPrimitive(const bool & IsButtonPressed ,
												 const int & X , const  int & Y)
{
	if (line->Down)                  //Проверяем какая кнопка какого
	   DrawLine(IsButtonPressed , X , Y);   //примитива нажата.
	else if (rectangle->Down)                // В случае определения, вызываем
	   DrawRectangle(IsButtonPressed , X ,Y);  //соответсвующий метод.
	else if (ellipse->Down)
	   DrawEllipse(IsButtonPressed , X , Y);
}
//----------------------------------------------------------------------------
inline void TMainForm::DrawLine(const bool & IsButtonPressed , const int & X ,
																  const int & Y)
{
	if (IsButtonPressed)                 //При первом заходе в метод, устанавлеваем
	   WorkSpace->Canvas->MoveTo(X , Y); //курсор в точку (X ,Y). Во втором заходе
	else if ( !IsButtonPressed )         //рисуем линию до точки заданной в
	   WorkSpace->Canvas->LineTo(X , Y); //LineTo.
}
//------------------------------------------------------------------------------
inline void TMainForm::DrawRectangle(const bool & IsButtonPressed , const int & X ,
																  const int & Y)
{
	static int tempX , tempY;       //При помощи статических локальных переменных
	if (IsButtonPressed)           //мы запоминаем левый верхних угол прямоугольник
	{                             //При втором заходе рисуем прямоугольник с
		tempX = X;               //ранее сохранёными координатами.
		tempY = Y;
	}
	else if ( !IsButtonPressed)
	{
		WorkSpace->Canvas->Rectangle(tempX , tempY , X , Y);
	}
}
//--------------------------------------------------------------------------------
inline void TMainForm::DrawEllipse(const bool & IsButtonPressed , const int & X ,
																  const int & Y)
{
	static int tempX , tempY;
	if (IsButtonPressed)
	{
		tempX = X;
		tempY = Y;
	}
	else if ( !IsButtonPressed)
	{
		WorkSpace->Canvas->Ellipse(tempX , tempY , X , Y);
	}
}
//------------------------------------------------------------------------------
inline void TMainForm::Erase(const int & X , const int & Y)
{
	WorkSpace->Canvas->Brush->Color = clWhite;       //Задаем область действия Erase
	WorkSpace->Canvas->FillRect(Rect(X - MagicNumber , Y - MagicNumber ,
									 X + MagicNumber , Y + MagicNumber));
	LineWidthChange(this);
	ColorLineChange(this);
	LineStyleChange(this);
	BrushColorChange(this);
	BrushStyleChange(this);
}
//------------------------------------------------------------------------------
inline void TMainForm::PenDraw(const int & X , const & Y)
{                                                         //Попиксельно рисуем
	WorkSpace->Canvas->Pixels[X][Y] = ColorLine->Selected; //карандашем.
}
//------------------------------------------------------------------------------
void __fastcall TMainForm::WorkSpaceMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	IsButtonPressed = true;                  //Запоминаем нажатие кнопки. В будущем
	WhichPrimitive(IsButtonPressed , X , Y); //оно нам понадобится.
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WorkSpaceMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	IsButtonPressed = false;
	WhichPrimitive(IsButtonPressed , X , Y);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LineWidthChange(TObject *Sender)
{                                                           //присваеваем выбранную
	WorkSpace->Canvas->Pen->Width = StrToInt(LineWidth->Text); //ширину линии.
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ColorLineChange(TObject *Sender)
{                                                        //присваеваем выбранный
	WorkSpace->Canvas->Pen->Color = ColorLine->Selected; //цвет линии.
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LineStyleChange(TObject *Sender)
{
	switch(LineStyle->ItemIndex)               //определяем стиль линий.
	{
		case 0 : WorkSpace->Canvas->Pen->Style = psSolid; break;
		case 1 : WorkSpace->Canvas->Pen->Style = psDash; break;
		case 2 : WorkSpace->Canvas->Pen->Style = psDot; break;
		case 3 : WorkSpace->Canvas->Pen->Style = psDashDot; break;
		case 4 : WorkSpace->Canvas->Pen->Style = psDashDotDot; break;
		case 5 : WorkSpace->Canvas->Pen->Style = psClear; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BrushColorChange(TObject *Sender)
{                                                           //задаем кисти
	WorkSpace->Canvas->Brush->Color = BrushColor->Selected; //выбранный цвет.
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BrushStyleChange(TObject *Sender)
{
	switch(BrushStyle->ItemIndex)                 //определяем стиль кисти
	{
		case 0 : WorkSpace->Canvas->Brush->Style = bsClear; break;
		case 1 : WorkSpace->Canvas->Brush->Style = bsCross; break;
		case 2 : WorkSpace->Canvas->Brush->Style = bsBDiagonal; break;
		case 3 : WorkSpace->Canvas->Brush->Style = bsHorizontal; break;
		case 4 : WorkSpace->Canvas->Brush->Style = bsSolid; break;
		case 5 : WorkSpace->Canvas->Brush->Style = bsDiagCross; break;
		case 6 : WorkSpace->Canvas->Brush->Style = bsFDiagonal; break;
		case 7 : WorkSpace->Canvas->Brush->Style = bsVertical; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WorkSpaceMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if (Eraser->Down)
	   Erase(X , Y);
	else if (Pen->Down && IsButtonPressed)
       PenDraw(X , Y);
}
//---------------------------------------------------------------------------
