object GLForm2D: TGLForm2D
  Left = 526
  Top = 89
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Formulario Principal'
  ClientHeight = 499
  ClientWidth = 500
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 232
    Top = 208
  end
  object MainMenu1: TMainMenu
    Left = 200
    Top = 208
    object Menu1: TMenuItem
      Caption = 'Menu'
      object F2: TMenuItem
        Caption = 'F'
        OnClick = F2Click
      end
      object R2: TMenuItem
        Caption = 'R'
        Enabled = False
        OnClick = R2Click
      end
    end
  end
end
