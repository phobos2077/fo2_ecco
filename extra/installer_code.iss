[code]


function ValidateRequirement(FileName: String; MessageId: String): Boolean;
begin
  result := true;
  if not(FileExists(ExpandConstant('{app}\'+FileName))) then
  begin
    if MsgBox(CustomMessage(MessageId),mbError,MB_YESNO) <> IDYES then
    begin
      result := false;
    end
  end
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  result:= true;
  if (curPageID = wpSelectDir) then
  begin
    if not(ValidateRequirement('fallout2.exe', 'WFalloutNotFound')) or
       not(ValidateRequirement('mods\rpu.dat', 'WRPNotFound')) or
       not(ValidateRequirement('mods\rpu_map_update.dat', 'WRPMapUpdateNotFound')) then
    begin
        result := false;
    end
  end
end;

// *********** clickable link
 var  
 MouseLabel,SiteLabel: TLabel;  
  
 procedure SiteLabelOnClick(Sender: TObject);  
 var  
 ErrorCode: Integer;  
 begin  
 ShellExec('open', 'http://www.nma-fallout.com/showthread.php?193578-Economy-and-Combat-Rebalance-mod', '', '', SW_SHOWNORMAL, ewNoWait, ErrorCode)  
 end;  
  
 procedure SiteLabelMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);  
 begin  
 SiteLabel.Font.Color:=clRed  
 end;  
  
 procedure SiteLabelMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);  
 begin  
 SiteLabel.Font.Color:=clBlue  
 end;  
  
 procedure SiteLabelMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);  
 begin  
 SiteLabel.Font.Color:=clGreen  
 end;  
  
 procedure SiteLabelMouseMove2(Sender: TObject; Shift: TShiftState; X, Y: Integer);  
 begin  
 SiteLabel.Font.Color:=clBlue  
 end;  

// components larger

type
  TPositionStorage = array of Integer;

var
  CompPageModified: Boolean;
  CompPagePositions: TPositionStorage;


//procedure SaveComponentsPage(out Storage: TPositionStorage);
//begin
//  SetArrayLength(Storage, 10);
//
//  Storage[0] := WizardForm.Height;
//  Storage[1] := WizardForm.NextButton.Top;
//  Storage[2] := WizardForm.BackButton.Top;
//  Storage[3] := WizardForm.CancelButton.Top;
//  Storage[4] := WizardForm.ComponentsList.Height;
//  Storage[5] := WizardForm.OuterNotebook.Height;
//  Storage[6] := WizardForm.InnerNotebook.Height;
//  Storage[7] := WizardForm.Bevel.Top;
//  Storage[8] := WizardForm.BeveledLabel.Top;
//  Storage[9] := WizardForm.ComponentsDiskSpaceLabel.Top;
//end;



//procedure LoadComponentsPage(const Storage: TPositionStorage;
//  HeightOffset: Integer);
//begin
//  if GetArrayLength(Storage) <> 10 then
//    RaiseException('Invalid storage array length.');
//
//  WizardForm.Height := Storage[0] + HeightOffset;
//  WizardForm.NextButton.Top := Storage[1] + HeightOffset;
//  WizardForm.BackButton.Top := Storage[2] + HeightOffset;
//  WizardForm.CancelButton.Top := Storage[3] + HeightOffset;
//  WizardForm.ComponentsList.Height := Storage[4] + HeightOffset;
//  WizardForm.OuterNotebook.Height := Storage[5] + HeightOffset;
//  WizardForm.InnerNotebook.Height := Storage[6] + HeightOffset;
//  WizardForm.Bevel.Top := Storage[7] + HeightOffset;
//  WizardForm.BeveledLabel.Top := Storage[8] + HeightOffset;
//  WizardForm.ComponentsDiskSpaceLabel.Top := Storage[9] + HeightOffset;
//end;


procedure AdjustSize(ctrl: TControl; widthOfs: Integer; heightOfs: Integer);
begin
  ctrl.Width := ctrl.Width + widthOfs;
  ctrl.Height := ctrl.Height + heightOfs;
end;

procedure AdjustPos(ctrl: TControl; widthOfs: Integer; heightOfs: Integer);
begin
  ctrl.Left := ctrl.Left + widthOfs;
  ctrl.Top := ctrl.Top + heightOfs;
end;


//procedure ResizeWizard(WidthOfs: Integer; HeightOfs: Integer);
//begin
//  AdjustPos(WizardForm, -WidthOfs div 2, -HeightOfs div 2);
//  AdjustSize(WizardForm, WidthOfs, HeightOfs);
//  with WizardForm do begin
//    AdjustPos(NextButton, WidthOfs, HeightOfs);
//    AdjustPos(BackButton, WidthOfs, HeightOfs);
//    AdjustPos(CancelButton, WidthOfs, HeightOfs);
//    AdjustPos(Bevel, 0, HeightOfs);
//    AdjustSize(Bevel, WidthOfs, 0);
//    AdjustSize(Bevel1, WidthOfs, 0);
//    AdjustPos(BeveledLabel, 0, HeightOfs);
//    AdjustPos(ComponentsDiskSpaceLabel, 0, HeightOfs);
//    AdjustSize(PageNameLabel, WidthOfs, 0);
//    AdjustSize(PageDescriptionLabel, WidthOfs, 0);
//    AdjustPos(WizardSmallBitmapImage, WidthOfs, 0);
//    AdjustSize(FilenameLabel, WidthOfs, 0);
//    AdjustPos(DirBrowseButton, WidthOfs, 0); 
//    AdjustSize(DirEdit, WidthOfs, 0); 
//    AdjustSize(SelectDirLabel, WidthOfs, 0);
//    AdjustSize(SelectComponentsLabel, WidthOfs, 0);
//    AdjustSize(SelectTasksLabel, WidthOfs, 0);
//    AdjustSize(TypesCombo, WidthOfs, 0); 
//    AdjustSize(MainPanel, WidthOfs, 0); 
//    AdjustSize(ComponentsList, WidthOfs, HeightOfs);
//    AdjustSize(OuterNotebook, WidthOfs, HeightOfs);
//    AdjustSize(InnerNotebook, WidthOfs, HeightOfs);
//    AdjustSize(InfoBeforeMemo, WidthOfs, HeightOfs);
//    AdjustSize(InfoAfterMemo, WidthOfs, HeightOfs);
//    AdjustSize(ReadyMemo, WidthOfs, HeightOfs);
//    AdjustSize(ProgressGauge, WidthOfs, 0);
//    AdjustSize(WizardBitmapImage, 0, HeightOfs);
//    AdjustSize(WizardBitmapImage2, 0, HeightOfs);
//  end;
//end;


procedure InitializeWizard();
begin
 //MouseLabel:=TLabel.Create(WizardForm)  
 //MouseLabel.Width:=WizardForm.Width  
 //MouseLabel.Height:=WizardForm.Height  
 //MouseLabel.Autosize:=False  
 //MouseLabel.Transparent:=True  
 //MouseLabel.OnMouseMove:=@SiteLabelMouseMove2  
 //MouseLabel.Parent:=WizardForm  
  
 SiteLabel:=TLabel.Create(WizardForm)  
 SiteLabel.Left:=10  
 SiteLabel.Top:=330  
 SiteLabel.Cursor:=crHand  
 SiteLabel.Font.Color:=clBlue  
 SiteLabel.Caption:='phobos2077 EcCo mod'  
 SiteLabel.OnClick:=@SiteLabelOnClick  
 SiteLabel.OnMouseDown:=@SiteLabelMouseDown  
 SiteLabel.OnMouseUp:=@SiteLabelMouseUp  
 SiteLabel.OnMouseMove:=@SiteLabelMouseMove  
 SiteLabel.Parent:=WizardForm  

 //ResizeWizard(200, 200);

 CompPageModified := False;
end;

