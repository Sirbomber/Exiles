#ifndef OP2COMMANDPANE_H
#define OP2COMMANDPANE_H

struct OP2CommandPaneView
{
  struct OP2CommandPaneViewVtbl
  {
    void (__thiscall *UpdateView)(OP2CommandPaneView *thisPtr); // 00
    void (__thiscall *OnAddView)(OP2CommandPaneView *thisPtr); // 04
    void (__thiscall *OnRemoveView)(OP2CommandPaneView *thisPtr); // 08
    int (__thiscall *IsNewView)(OP2CommandPaneView *thisPtr); // 0c
    int unk1; // 10 purecall
    void (__thiscall *SetReportPageIndex)(OP2CommandPaneView *thisPtr); // 14
    int (__thiscall *DoesUnitSelectionChangeCauseUpdate)(OP2CommandPaneView *thisPtr); // 18
    void (__thiscall *OnAction)(OP2CommandPaneView *thisPtr); // 1c
    int (__thiscall *GetSelectedReportButtonIndex)(OP2CommandPaneView *thisPtr); // 20
  } *vtbl; // 00
  // TODO fill this crap in
};

#endif
