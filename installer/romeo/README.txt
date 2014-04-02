Instruction for ROMEO installation:

1) Install the codec package ffdshow found in the extracted folder for your platform:
	- ffdshow_rev4530_20140209_clsid.exe for 32bit architecture
	- ffdshow_rev4530_20140209_clsid_x64.exe for 64bit architecture

2)During the installation process verify that VFW Interface is checked in the components section and that the wanted video codec are selected in the next section.

3)If you used the 32bit installer, after the installation open from the Start Menu VFW Configuration. In the Decoder tab select Supported Codecs on the left.
Then find the MJPEG Codec and enable it to use libavcodec. 

4) Open RomeoInstaller.exe and follow the installation instructions.

For errors arising with the opening of images and video open the ffdshow configuration and decoder mangager to see which codecs are enabled.

More information and step-by-step guide can be found in the Installation Manual.

For additional support or installation problems contact:
hurryupswe@gmail.com