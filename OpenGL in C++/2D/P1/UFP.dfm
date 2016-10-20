object GLForm2D: TGLForm2D
  Left = 214
  Top = 112
  Width = 408
  Height = 434
  Caption = 'Formulario Principal'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    Left = 8
    Top = 8
    object Precisar1: TMenuItem
      Caption = 'Precisar'
      OnClick = Precisar1Click
    end
    object Acercar1: TMenuItem
      Caption = 'Acercar'
      OnClick = Acercar1Click
    end
    object Alejar1: TMenuItem
      Caption = 'Alejar'
      OnClick = Alejar1Click
    end
    object Trasladar1: TMenuItem
      Caption = 'Trasladar'
      OnClick = Trasladar1Click
    end
    object Centrar1: TMenuItem
      Caption = 'Centrar'
      OnClick = Centrar1Click
    end
    object Tiling1: TMenuItem
      Caption = 'Tiling'
      OnClick = Tiling1Click
    end
    object Opcional1: TMenuItem
      Caption = 'Opcional'
      object Valores1: TMenuItem
        Caption = 'Valores'
        OnClick = Valores1Click
      end
      object Animacin2: TMenuItem
        Caption = 'Animación'
        OnClick = Animacin2Click
      end
      object Colores1: TMenuItem
        Caption = 'Colores'
        OnClick = Colores1Click
      end
    end
  end
end
