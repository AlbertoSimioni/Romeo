function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (installer.value("os") === "win") {
        component.addOperation("CreateShortcut", "@TargetDir@/romeo.exe", "@StartMenuDir@/Romeo.lnk");


        component.addOperation("CreateShortcut", "@TargetDir@/romeo.exe", "@DesktopDir@/Romeo.lnk");
    }
}
