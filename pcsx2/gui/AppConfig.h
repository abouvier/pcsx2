/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2010  PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "AppForwardDefs.h"
#include "PathDefs.h"
#include "CDVD/CDVDaccess.h"
#include <memory>

enum DocsModeType
{
	// uses /home/user or /cwd for the program data.  This is the default mode and is the most
	// friendly to modern computing security requirements; as it isolates all file modification
	// to a zone of the hard drive that has granted write permissions to the user.
	DocsFolder_User,
	
	// uses a custom location for program data. Typically the custom folder is either the
	// absolute or relative location of the program -- absolute is preferred because it is
	// considered more secure by MSW standards, due to DLL search rules.
	//
	// To enable PCSX2's "portable" mode, use this setting and specify "." for the custom
	// documents folder.
	DocsFolder_Custom,
};

extern wxDirName		SettingsFolder;				// dictates where the settings folder comes from, *if* UseDefaultSettingsFolder is FALSE.

extern wxDirName GetSettingsFolder();

extern wxDirName GetCheatsFolder();
extern wxDirName GetCheatsWsFolder();

enum AspectRatioType
{
	AspectRatio_Stretch,
	AspectRatio_4_3,
	AspectRatio_16_9,
	AspectRatio_MaxCount
};

enum FMVAspectRatioSwitchType
{
	FMV_AspectRatio_Switch_Off,
	FMV_AspectRatio_Switch_4_3,
	FMV_AspectRatio_Switch_16_9,
	FMV_AspectRatio_Switch_MaxCount
};

enum MemoryCardType
{
	MemoryCard_None,
	MemoryCard_File,
	MemoryCard_Folder,
	MemoryCard_MaxCount
};

// =====================================================================================================
//  Pcsx2 Application Configuration. 
// =====================================================================================================

class AppConfig
{
public:
	// ------------------------------------------------------------------------
	struct FolderOptions
	{
		BITFIELD32()
			bool
				UseDefaultBios:1,
				UseDefaultSavestates:1,
				UseDefaultMemoryCards:1,
				UseDefaultCheats:1,
				UseDefaultCheatsWS:1;
		BITFIELD_END

		wxDirName
			Bios,
			Savestates,
			MemoryCards,
			Cheats,
			CheatsWS;

		wxFileName RunDisc;		// last used location for Disc loading.

		FolderOptions();
		void LoadSave( IniInterface& conf );
		void ApplyDefaults();

		void Set( FoldersEnum_t folderidx, const wxString& src, bool useDefault );

		const wxDirName& operator[]( FoldersEnum_t folderidx ) const;
		wxDirName& operator[]( FoldersEnum_t folderidx );
		bool IsDefault( FoldersEnum_t folderidx ) const;
	};

	// ------------------------------------------------------------------------
	struct FilenameOptions
	{
		wxFileName Bios;
		wxFileName Plugins[PluginId_Count];

		void LoadSave( IniInterface& conf );

		const wxFileName& operator[]( PluginsEnum_t pluginidx ) const;
	};

	// ------------------------------------------------------------------------
	// Options struct for each memory card.
	//
	struct McdOptions
	{
		wxFileName	Filename;	// user-configured location of this memory card
		bool		Enabled;	// memory card enabled (if false, memcard will not show up in-game)
		MemoryCardType Type;	// the memory card implementation that should be used
	};

	// ------------------------------------------------------------------------
	// The GS window receives much love from the land of Options and Settings.
	//
	struct GSWindowOptions
	{
		AspectRatioType AspectRatio;
		FMVAspectRatioSwitchType FMVAspectRatioSwitch;

		GSWindowOptions();

		void LoadSave( IniInterface& conf );
		void SanityCheck();
	};

	struct FramerateOptions
	{
		bool		SkipOnLimit;
		bool		SkipOnTurbo;

		Fixed100	NominalScalar;
		Fixed100	TurboScalar;
		Fixed100	SlomoScalar;

		FramerateOptions();
		
		void LoadSave( IniInterface& conf );
		void SanityCheck();
	};

public:
	// uses automatic ntfs compression when creating new memory cards (Win32 only)
#ifdef __WXMSW__
	bool		McdCompressNTFS;
#endif

	// Master toggle for enabling or disabling all speedhacks in one fail-free swoop.
	// (the toggle is applied when a new EmuConfig is sent through AppCoreThread::ApplySettings)
	bool		EnableSpeedHacks;
	bool		EnableGameFixes;
	bool		EnableFastBoot;

	// Presets try to prevent users from overwhelming when they want to change settings (usually to make a game run faster).
	// The presets allow to modify the balance between emulation accuracy and emulation speed using a pseudo-linear control.
	// It's pseudo since there's no way to arrange groups of all of pcsx2's settings such that each next group makes it slighty faster and slightly less compatiible for all games.
	//However, By carefully selecting these preset config groups, it's hopefully possible to achieve this goal for a reasonable percentage (hopefully above 50%) of the games.
	//when presets are enabled, the user has practically no control over the emulation settings, and can only choose the preset to use.

	// The next 2 vars enable/disable presets alltogether, and select/reflect current preset, respectively.
	bool		EnablePresets;
	int			PresetIndex;

	wxString				CurrentIso;
    wxString				CurrentBlockdump;
	wxString				CurrentELF;
	wxString				CurrentIRX;
	CDVD_SourceType			CdvdSource;
	wxString				CurrentGameArgs;

	// Memorycard options - first 2 are default slots, last 6 are multitap 1 and 2
	// slots (3 each)
	McdOptions				Mcd[8];
	wxString				GzipIsoIndexTemplate; // for quick-access index with gzipped ISO
	FolderOptions			Folders;
	FilenameOptions			BaseFilenames;
	GSWindowOptions			GSWindow;
	FramerateOptions		Framerate;
	
	// PCSX2-core emulation options, which are passed to the emu core prior to initiating
	// an emulation session.  Note these are the options saved into the GUI ini file and
	// which are shown as options in the gui preferences, but *not* necessarily the options
	// used by emulation.  The gui allows temporary per-game and commandline level overrides.
	Pcsx2Config				EmuOptions;

public:
	AppConfig();

	wxString FullpathToBios() const;
	wxString FullpathToMcd( uint slot ) const;

	void LoadSave( IniInterface& ini );
	void LoadSaveRootItems( IniInterface& ini );
	void LoadSaveMemcards( IniInterface& ini );

	static int  GetMaxPresetIndex();
	
	bool IsOkApplyPreset(int n, bool ignoreMTVU);
	void ResetPresetSettingsToDefault();
};

void AppSaveSettings();
extern void AppApplySettings();

extern void AppConfig_OnChangedSettingsFolder();

extern std::unique_ptr<AppConfig> g_Conf;
