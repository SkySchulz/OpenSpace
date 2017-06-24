local seedPointsFileBatsrus = '${OpenSpace_MagJul2012_051017_1_1day_15secondsTA}/scene/fieldlinessequence/seedpoints/BATS_R_US_all_combined.txt';
-- local seedPointsFileEnlil = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil.txt';
-- local eqSeedsEnlil2AU = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/equitorialslice2_AU.txt';
-- local eqSeedsEnlil1AU_1nHalfdeg = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/equitorialslice1_AU_1.5deg.txt';
-- local eqSeedsEnlil_0n11AU_2deg = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/equitorialslice_0.11AU_2deg.txt';

-- local enlilBinaryFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/step_length_0.99/30000MaxPoints_0.11AU_2deg/';
-- local enlilBinaryFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/20000MaxPoints_0.11AU_2deg/';

-- local binaryFolderEnlilTest = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/test/';
-- local binaryFolderEnlilTestDownsampled = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/test/downsampled/';
-- local binaryFolderEnlilHiResDownsampled = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/20000MaxPoints_0.11AU_2deg/downsampled/';
-- local binaryFolderEnlilHiResComparison = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/20000MaxPoints_0.11AU_2deg/comparison/';

-- -- local volumeFolderBatsrus = '${OPENSPACE_DATA}/bats_sequence';
-- local volumeFolderBatsrus = '${OPENSPACE_DATA}/new_bats';
-- -- local volumeFolderEnlil = '${OPENSPACE_DATA}/enlil_sequence';
-- local volumeFolderEnlil = '${OPENSPACE_DATA}/ENLIL_JULY_2012';
-- -- local volumeFolderEnlil = '${OPENSPACE_DATA}/Ailsa';
-- local volumeFile1 = '${OPENSPACE_DATA}/bats_sequence/batsrus1.cdf';
-- local volumeFile2 = '${OPENSPACE_DATA}/bats_sequence/batsrus2.cdf';
-- local volumeFile3 = '${OPENSPACE_DATA}/bats_sequence/batsrus3.cdf';
-- local volumeFileEnlil = '${OPENSPACE_DATA}/Ailsa/Ailsa_Prise_101414_SH_1.enlil.0001.cdf';

local R_E_TO_METER = 6371000;
local R_S_TO_METER = 695700000;
local A_U_TO_METER = 149597870700;
local volumeFolderEnlilHighRes = '${OPENSPACE_DATA}/ENLIL_JULY_2012_HI-RES';

local volumeFolderBatsrus60Sec  = '/media/ccarlbau/c5bf076c-80aa-44e1-aada-f1064215ab0f/OpenSpace_MagJul2012_051017_1_fullrun_1minute';
local volumeFolderBatsrus15Sec = '/media/ccarlbau/c5bf076c-80aa-44e1-aada-f1064215ab0f/OpenSpace_MagJul2012_051017_1_1day_15seconds';

-- local binaryFolderEnlilHiRes_1                = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/30000MaxPoints_0.11AU_4deg_1/';
-- local binaryFolderEnlilHiRes_1_downsampled    = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/30000MaxPoints_0.11AU_4deg_1/downsampled/';
-- local binaryFolderEnlilHiRes_2                = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/30000MaxPoints_0.11AU_4deg_2/';

-- local binaryFolderEnlilHiRes_1_downsampled_x2 = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/30000MaxPoints_0.11AU_4deg_1/downsampled/downsampled/';
-- local binaryFolderEnlilHiRes_1_downsampled_x3 = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2/30000MaxPoints_0.11AU_4deg_1/downsampled/downsampled/downsampled/';

local eqSeedsEnlil_0n11AU_4deg_1 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/equitorialslice_0.11AU_4deg_1.txt';
local eqSeedsEnlil_0n11AU_4deg_2 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/equitorialslice_0.11AU_4deg_2.txt';

local seeds_Enlil_0n11AU_positive10Lat_4deg_1 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_0.11AU_lat10_4deg_1.txt';
local seeds_Enlil_0n11AU_positive10Lat_4deg_2 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_0.11AU_lat10_4deg_2.txt';

local seeds_Enlil_0n11AU_negative10Lat_4deg_1 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_0.11AU_lat-10_4deg_1.txt';
local seeds_Enlil_0n11AU_negative10Lat_4deg_2 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_0.11AU_lat-10_4deg_2.txt';

local seeds_Enlil_4deg = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil4deg.txt';


local seeds_aroundEarth_13th1800 = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/earth13th1800.txt';

local binaryFolderEnlilHiRes_0lat_1           = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2_30kMaxPoints/eq_plane/0.11AU_4deg_1/';
local binaryFolderEnlilHiRes_Pos10Lat_1       = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2_30kMaxPoints/lat_+10/0.11AU_4deg_1/';
local binaryFolderEnlilHiRes_Neg10Lat_1       = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/hi-res/step_length_0.2_30kMaxPoints/lat_-10/0.11AU_4deg_1/';

local batsrusBinaryFolder15Sec = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_batsrus_2012_July/15_second_set/old_seeds/';
local batsrusBinaryFolder60Sec = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_batsrus_2012_July/60_second_set/old_seeds/';

local batsrusBinaryFolder15SecStatic100 = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_batsrus_2012_July/15_second_set/100_static_seeds/';
local batsrusBinaryFolder60SecStatic100 = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_batsrus_2012_July/60_second_set/100_static_seeds/';

local seedsCME = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/cme1latitude.txt';

local seedPointsFileEnlil = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/100_static_batsrus_seeds.txt';

local jsonFromAsher = '${OPENSPACE_DATA}/scene/fieldlinessequence/json_from_asher/';
local jsonFromAsherDwnSmpldBin8 = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_batsrus_2012_July/OpenSpace_MagJul2012_051017_1_20120714_ALL_BINARY_dwnsmpl8/';

local lutzMagJsonPath = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/june22nd/json/flowlinedata_B_20000101/';
local lutzMagBinaryPath = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/june22nd/binaries/flowlinedata_B_20000101/';
local lutzFlowJsonPath = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/june22nd/json/flowlinedata_V_20000101/';
local lutzFlowBinaryPath = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/june22nd/binaries/flowlinedata_V_20000101/';

local userSelected = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/user_selected/';
local magnetic = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/magnetic/';
local lutzBinaryPath = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/june23rd/binaries/user_selected/';

local lutzEventFlowJson = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/flow/14/';
local lutzEventFlowBinary = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/binary/flow/';

local lutzEventMagneticJson = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/';
local lutzEventMagneticBinary = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/binary/magnetic/';




return {
    {
        Name = "HNMReferenceFrame",
        Parent = "SolarSystemBarycenter",
        Transform = {
            Rotation = {
                Type = "SpiceRotation",
                SourceFrame = "HEEQ180",
                DestinationFrame = "GALACTIC",
                Kernels = "${OPENSPACE_DATA}/scene/fieldlinessequence/customkernels/HNM-enlil_ref_frame.tf",
            },
        },
    },
    {
        Name = "GSMReferenceFrame",
        Parent = "EarthBarycenter",
        Transform = {
            Rotation = {
                Type = "SpiceRotation",
                SourceFrame = "GSM",
                DestinationFrame = "GALACTIC",
                Kernels = "${OPENSPACE_DATA}/scene/fieldlinessequence/customkernels/GSM.ti",
            },
        },
    },



    -- {
    --     Name = "ENLIL_lat4_1",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreProcess",

    --         SourceFolder = volumeFolderEnlilHighRes,

    --         StartStateOffset = 0,
    --         -- StateStepSize = 16,
    --         -- MaxNumStates = 0,

    --         TracingVariable = "b", -- "b" is the variable specifying the magnetic field
    --         MaximumTracingSteps = 30000.0,

    --         OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new/1AU_lat4_1/',
    --         ExtraVariables          = "rho",
    --         ExtraMagnitudeVariables = "ur utheta uphi",

    --         SeedPointInfo = {
    --             File = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_1AU_lat4deg_4degIncrements_1.txt',
    --         }
    --     }
    -- },

    -- {
    --     Name = "ENLIL_lat4_2",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreProcess",

    --         SourceFolder = volumeFolderEnlilHighRes,

    --         StartStateOffset = 0,
    --         -- StateStepSize = 16,
    --         -- MaxNumStates = 0,

    --         TracingVariable = "b", -- "b" is the variable specifying the magnetic field
    --         MaximumTracingSteps = 30000.0,

    --         OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new/1AU_lat4_2/',
    --         ExtraVariables          = "rho",
    --         ExtraMagnitudeVariables = "ur utheta uphi",

    --         SeedPointInfo = {
    --             File = '${OPENSPACE_DATA}/scene/fieldlinessequence/seedpoints/enlil_1AU_lat4deg_4degIncrements_2.txt',
    --         }
    --     }
    -- },


    -- {
    --     Name = "ENLIL_earth",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreProcess",

    --         SourceFolder = volumeFolderEnlilHighRes,

    --         StartStateOffset = 0,
    --         -- StateStepSize = 16,
    --         MaxNumStates = 1,

    --         TracingVariable = "b", -- "b" is the variable specifying the magnetic field
    --         MaximumTracingSteps = 30000.0,

    --         OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new/earth/05',
    --         ExtraVariables          = "rho",
    --         ExtraMagnitudeVariables = "ur utheta uphi",

    --         SeedPointInfo = {
    --             File = '/home/ccarlbau/Desktop/earth_seeds/earth_seeds0.txt',
    --         }
    --     }
    -- },


    -- {
    --     Name = "ENLIL_superrun",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreProcess",

    --         -- SourceFolder = '/home/ccarlbau/workspace/OpenSpace/data/ENLIL_JULY_2012_HiRes',
    --         -- SourceFolder = '/media/ccarlbau/92424c03-957d-4b19-874d-1c20837d81b6/Oskar_Carlbaum_051717_SH_2',
    --         -- SourceFolder = '/media/ccarlbau/42a9eae3-e5e0-4d94-b439-f634d48b0d8c/Oskar_Carlbaum_060717_SH_3/3D_CDF',
    --         SourceFolder = '/media/ccarlbau/ff854077-f4bf-4644-a94b-1fe2d8824c64/Oskar_Carlbaum_061617_SH_1/3D_CDF',

    --         -- StartStateOffset = 168,
    --         -- StateStepSize = 16,
    --         -- MaxNumStates = 1,

    --         TracingVariable = "b", -- "b" is the variable specifying the magnetic field
    --         MaximumTracingSteps = 30000.0,

    --         -- OutputLocationBinary    = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new/earth/05',
    --         ExtraVariables          = "rho",
    --         ExtraMagnitudeVariables = "ur utheta uphi",

    --         SeedPointInfo = {
    --             File = '/home/ccarlbau/Desktop/earth_seeds/earth_seeds000.txt',
    --         }
    --     }
    -- },




    -- {
    --     Name = "Fieldlines_ENLIL_slice_eqPlane_1",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/011AU_eq_1/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },

    -- {
    --     Name = "Fieldlines_ENLIL_slice_eqPlane_2",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/011AU_eq_2/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },

    -- {
    --     Name = "Fieldlines_ENLIL_slice_lat4_1",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/1AU_lat4_1/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },
    -- {
    --     Name = "Fieldlines_ENLIL_slice_lat4_2",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/1AU_lat4_2/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },

    -- {
    --     Name = "Fieldlines_ENLIL_earth",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/earth/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },
    -- {
    --     Name = "Fieldlines_ENLIL_stereoa",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/stereoa/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },




    -- --------
    -- {
    --     Name = "Fieldlines_ENLIL_slice_eqPlane_1AU_1",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/1AU_eq_1/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },

    -- {
    --     Name = "Fieldlines_ENLIL_slice_eqPlane_1AU_2",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/1AU_eq_2/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },

    -- {
    --     Name = "Fieldlines_ENLIL_slice_lat4_011AU_1",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/011AU_lat4_1/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },
    -- {
    --     Name = "Fieldlines_ENLIL_slice_lat4_011AU_2",
    --     Parent = "HNMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/binary_enlil_2012_July/new_originals/011AU_lat4_2/downsampled40/',
    --         -- StartStateOffset = 309,
    --         -- MaxNumStates = 1,
    --          ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/enlil_density.txt',
    --             '${OPENSPACE_DATA}/colortables/kroyw.txt',
    --         },
    --         ColorTableMinMax = {{0, 1000000},{100, 2000},},
    --         ExtraMinMaxLimits = {{-1, 10000000},{0, 5000},},
    --         LoadBinariesAtRuntime = true,
    --         DefaultColor = {0.7,0.4,0,0.07},
    --     },
    --     Tag = {"fieldline_sequence", "fieldline_enlil"},
    -- },
    -- --------


    -- {
    --     Name = "Fieldlines_PFSS_Asher",
    --     Parent = "Sun",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         -- TracingMethod = "PreTracedJson",
    --         TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = jsonFromAsher,
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/PFSS/',
    --         -- StartStateOffset = 515,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/',
    --         OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/PFSS/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/pfss_transition.txt',
    --             '${OPENSPACE_DATA}/colortables/pfss_topology.txt',
    --             '${OPENSPACE_DATA}/colortables/pfss_bsign.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 1},
    --             {0, 2},
    --             {-1, 1},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1},
    --             {0, 2},
    --             {-1, 1},
    --         },
    --     },
    -- },





 







    -- {
    --     Name = "Fieldlines_BATSRUS_Lutz_polar_closed",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         -- TracingMethod = "PreTracedJson",
    --         TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = jsonFromAsher,
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/polar/',
    --         -- StartStateOffset = 515,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/polar/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_transition.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 1000000},
    --             {0, 60},
    --             {-0.0225, 0.0225},
    --             {-10, 10},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 100000000},
    --             {-1, 150},
    --             {-0.12, 0.12},
    --             {-10, 10},
    --             {0, 3},
    --         },
    --     },
    -- },

   



   -- {
   --      Name = "Fieldlines_PFSS_Asher_Aligned2020",
   --      Parent = "HNMReferenceFrame",
   --      Renderable = {
   --          Type = "RenderableFieldlinesSequence",
   --          TracingMethod = "PreTracedJson",
   --          -- TracingMethod = "PreTracedBinary",
   --          -- SourceFolder = jsonFromAsher,
   --          -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
   --          -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/reversed/',
   --          SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/2020/',
   --          -- StartStateOffset = 515,
   --          -- StateStepSize = 100,
   --          -- MaxNumStates = 55,
   --          -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/',
   --          OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/2020/',
   --          -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/reversed/',
   --          -- OutputLocationBinary = batsrusBinaryFolder,
   --          ColorTablePaths = {
   --              -- '${OPENSPACE_DATA}/colortables/pfss_transition.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_topology.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_bsign.txt',
   --          },
   --          ColorTableMinMax = {
   --              -- {0, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --          ExtraMinMaxLimits = {
   --              -- {-1, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --      },
   --  },
   --  {
   --      Name = "Fieldlines_PFSS_Asher_Aligned2040",
   --      Parent = "HNMReferenceFrame",
   --      Renderable = {
   --          Type = "RenderableFieldlinesSequence",
   --          TracingMethod = "PreTracedJson",
   --          -- TracingMethod = "PreTracedBinary",
   --          -- SourceFolder = jsonFromAsher,
   --          -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
   --          SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/2040/',
   --          -- StartStateOffset = 515,
   --          -- StateStepSize = 100,
   --          -- MaxNumStates = 55,
   --          -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/',
   --          OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/2040/',
   --          -- OutputLocationBinary = batsrusBinaryFolder,
   --          ColorTablePaths = {
   --              -- '${OPENSPACE_DATA}/colortables/pfss_transition.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_topology.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_bsign.txt',
   --          },
   --          ColorTableMinMax = {
   --              -- {0, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --          ExtraMinMaxLimits = {
   --              -- {-1, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --      },
   --  },
   --  {
   --      Name = "Fieldlines_PFSS_Asher_Aligned3060",
   --      Parent = "HNMReferenceFrame",
   --      Renderable = {
   --          Type = "RenderableFieldlinesSequence",
   --          TracingMethod = "PreTracedJson",
   --          -- TracingMethod = "PreTracedBinary",
   --          -- SourceFolder = jsonFromAsher,
   --          -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
   --          SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/3060/',
   --          -- StartStateOffset = 515,
   --          -- StateStepSize = 100,
   --          -- MaxNumStates = 55,
   --          -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/',
   --          OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/grid/new_rot/3060/',
   --          -- OutputLocationBinary = batsrusBinaryFolder,
   --          ColorTablePaths = {
   --              -- '${OPENSPACE_DATA}/colortables/pfss_transition.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_topology.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_bsign.txt',
   --          },
   --          ColorTableMinMax = {
   --              -- {0, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --          ExtraMinMaxLimits = {
   --              -- {-1, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --      },
    -- },
   -- {
   --      Name = "Fieldlines_PFSS_LeilaNew",
   --      Parent = "HNMReferenceFrame",
   --      Renderable = {
   --          Type = "RenderableFieldlinesSequence",
   --          TracingMethod = "PreTracedJson",
   --          -- TracingMethod = "PreTracedBinary",
   --          -- SourceFolder = jsonFromAsher,
   --          -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
   --          SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/new/',
   --          -- StartStateOffset = 515,
   --          -- StateStepSize = 100,
   --          -- MaxNumStates = 55,
   --          -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/',
   --          OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/pfss_aligned/new/new/',
   --          -- OutputLocationBinary = batsrusBinaryFolder,
   --          ColorTablePaths = {
   --              -- '${OPENSPACE_DATA}/colortables/pfss_transition.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_topology.txt',
   --              '${OPENSPACE_DATA}/colortables/pfss_bsign.txt',
   --          },
   --          ColorTableMinMax = {
   --              -- {0, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --          ExtraMinMaxLimits = {
   --              -- {-1, 1},
   --              {0, 2},
   --              {-1, 1},
   --          },
   --      },
   --  },

    -- {
    --     Name = "Fieldlines_BATSRUS_Lutz_flowlines",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         -- TracingMethod = "PreTracedJson",
    --         TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = jsonFromAsher,
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/',
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/flow/',
    --         -- StartStateOffset = 515,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/flow/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/polar/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_transition.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 1000000},
    --             {0, 60},
    --             {-0.0225, 0.0225},
    --             {-10, 10},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 100000000},
    --             {-1, 150},
    --             {-0.12, 0.12},
    --             {-10, 10},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 200},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --     },
    -- },




    -- {
    --     Name = "Flowlines_BATSRUS_Lutz_EVENT_throughout",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedJson",
    --         -- TracingMethod = "PreTracedBinary",
    --         SourceFolder = lutzEventFlowJson..'throughout/',
    --         -- SourceFolder = lutzFlowBinaryPath..'throughout/downsampled4/',
    --         -- SourceFolder = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/flow/throughout/',
    --         -- StartStateOffset = 92,
    --         -- StateStepSize = 100,
    --         MaxNumStates = 907,
    --         OutputLocationBinary = lutzEventFlowBinary..'throughout/',
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },
    -- {
    --     Name = "Flowlines_BATSRUS_Lutz_EVENT_upstream",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedJson",
    --         -- TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = lutzJsonPath..'upstream/',
    --         -- SourceFolder = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/flow/upstream/',
    --         SourceFolder = lutzEventFlowJson..'upstream/',
    --         -- StartStateOffset = 108,--108, -- 130 and forward ARE FINE!
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 15,--75,
    --         OutputLocationBinary = lutzEventFlowBinary..'upstream/',
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },
    -- {
    --     Name = "Fieldlines_BATSRUS_Lutz_open-closed",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedJson",
    --         -- TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = lutzJsonPath..'open-closed/',
    --         -- SourceFolder = magnetic..'open-closed/',
    --         SourceFolder = lutzEventMagneticJson..'open-closed/',
    --         StartStateOffset = 2970,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         OutputLocationBinary = lutzEventMagneticBinary..'open-closed/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },

    -- {
    --     Name = "Fieldlines_BATSRUS_Lutz_throughout",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedJson",
    --         -- TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = lutzJsonPath..'open-closed/',
    --         -- SourceFolder = magnetic..'open-closed/',
    --         SourceFolder = lutzEventMagneticJson..'throughout/',
    --         -- StartStateOffset = 2190,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         OutputLocationBinary = lutzEventMagneticBinary..'throughout/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },








   -- {
   --      Name = "Flowlines_BATSRUS_Lutz_user_selected",
   --      Parent = "GSMReferenceFrame",
   --      Renderable = {
   --          Type = "RenderableFieldlinesSequence",
   --          TracingMethod = "PreTracedJson",
   --          -- TracingMethod = "PreTracedBinary",
   --          -- SourceFolder = lutzJsonPath..'throughout/',
   --          SourceFolder = userSelected, -- lutzFlowBinaryPath..'throughout/downsampled4/',
   --          -- SourceFolder = lutzBinaryPath, -- lutzFlowBinaryPath..'throughout/downsampled4/',
   --          -- StartStateOffset = 92,
   --          -- StateStepSize = 100,
   --          -- MaxNumStates = 65,
   --          OutputLocationBinary = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/binary/model_run/user_selected/',
   --          ColorTablePaths = {
   --              '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
   --              '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
   --              '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
   --              '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
   --              '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
   --          },
   --          ColorTableMinMax = {
   --              {0, 100000000},
   --              {0, 5},
   --              {-0.0125, 0.0125},
   --              {100, 450},
   --              {0, 3},
   --          },
   --          ExtraMinMaxLimits = {
   --              {-1, 1000000000},
   --              {-1, 20},
   --              {-0.12, 0.12},
   --              {-1, 5000},
   --              {0, 3},
   --          },
   --          RadialDomainLimits = {0, 500},
   --          CartesianDomainLimits = {
   --              {-300, 50},
   --              {-50, 50},
   --              {-50, 50},
   --          },
   --          LoadBinariesAtRuntime = true,
   --      },
   --  },






































































-- ----------------------ONLY FINISHED BINARIES BELOW THIS LINE!!!!! ----------------------




    -- --    {
    -- --     Name = "Fieldlines_BATSRUS_Lutz_circles",
    -- --     Parent = "GSMReferenceFrame",
    -- --     Renderable = {
    -- --         Type = "RenderableFieldlinesSequence",
    -- --         -- TracingMethod = "PreTracedJson",
    -- --         TracingMethod = "PreTracedBinary",
    -- --         SourceFolder = lutzMagBinaryPath..'circles/downsampled4/',
    -- --         -- SourceFolder = lutzJsonPath..'circles/',
    -- --         -- StartStateOffset = 515,
    -- --         -- StateStepSize = 100,
    -- --         -- MaxNumStates = 55,
    -- --         -- OutputLocationBinary = lutzBinaryPath..'circles/',
    -- --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    -- --         -- OutputLocationBinary = batsrusBinaryFolder,
    -- --         ColorTablePaths = {
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    -- --         },
    -- --         ColorTableMinMax = {
    -- --             {0, 100000000},
    -- --             {0, 5},
    -- --             {-0.0125, 0.0125},
    -- --             {100, 450},
    -- --             {0, 3},
    -- --         },
    -- --         ExtraMinMaxLimits = {
    -- --             {-1, 1000000000},
    -- --             {-1, 20},
    -- --             {-0.12, 0.12},
    -- --             {-1, 5000},
    -- --             {0, 3},
    -- --         },
    -- --         RadialDomainLimits = {0, 500},
    -- --         CartesianDomainLimits = {
    -- --             {-300, 50},
    -- --             {-50, 50},
    -- --             {-50, 50},
    -- --         },
    -- --         LoadBinariesAtRuntime = true,
    -- --     },
    -- -- },
    -- -- {
    -- --     Name = "Fieldlines_BATSRUS_Lutz_polar",
    -- --     Parent = "GSMReferenceFrame",
    -- --     Renderable = {
    -- --         Type = "RenderableFieldlinesSequence",
    -- --         -- TracingMethod = "PreTracedJson",
    -- --         TracingMethod = "PreTracedBinary",
    -- --         -- SourceFolder = lutzJsonPath..'polar/',
    -- --         SourceFolder = lutzMagBinaryPath..'polar/downsampled4/',
    -- --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/polar/',
    -- --         -- StartStateOffset = 515,
    -- --         -- StateStepSize = 100,
    -- --         -- MaxNumStates = 55,
    -- --         -- OutputLocationBinary = lutzBinaryPath..'polar/',
    -- --         ColorTablePaths = {
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    -- --         },
    -- --         ColorTableMinMax = {
    -- --             {0, 100000000},
    -- --             {0, 5},
    -- --             {-0.0125, 0.0125},
    -- --             {100, 450},
    -- --             {0, 3},
    -- --         },
    -- --         ExtraMinMaxLimits = {
    -- --             {-1, 1000000000},
    -- --             {-1, 20},
    -- --             {-0.12, 0.12},
    -- --             {-1, 5000},
    -- --             {0, 3},
    -- --         },
    -- --         RadialDomainLimits = {0, 500},
    -- --         CartesianDomainLimits = {
    -- --             {-300, 50},
    -- --             {-50, 50},
    -- --             {-50, 50},
    -- --         },
    -- --         LoadBinariesAtRuntime = true,
    -- --     },
    -- -- },
    -- {
    --     Name = "Fieldlines_BATSRUS_Lutz_throughout",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         -- TracingMethod = "PreTracedJson",
    --         TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = lutzJsonPath..'throughout/',
    --         SourceFolder = lutzMagBinaryPath..'throughout/downsampled4/',
    --         -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/polar/',
    --         -- StartStateOffset = 515,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         -- OutputLocationBinary = lutzBinaryPath..'throughout/',
    --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    --         -- OutputLocationBinary = batsrusBinaryFolder,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },
    -- -- {
    -- --     Name = "Fieldlines_BATSRUS_Lutz_open-closed",
    -- --     Parent = "GSMReferenceFrame",
    -- --     Renderable = {
    -- --         Type = "RenderableFieldlinesSequence",
    -- --         -- TracingMethod = "PreTracedJson",
    -- --         TracingMethod = "PreTracedBinary",
    -- --         -- SourceFolder = lutzJsonPath..'open-closed/',
    -- --         -- SourceFolder = magnetic..'open-closed/',
    -- --         SourceFolder = lutzMagBinaryPath..'open-closed/downsampled4/',
    -- --         -- StartStateOffset = 515,
    -- --         -- StateStepSize = 100,
    -- --         -- MaxNumStates = 55,
    -- --         -- OutputLocationBinary = lutzBinaryPath..'open-closed/',
    -- --         -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/lutz/last_closed/',
    -- --         -- OutputLocationBinary = batsrusBinaryFolder,
    -- --         ColorTablePaths = {
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    -- --         },
    -- --         ColorTableMinMax = {
    -- --             {0, 100000000},
    -- --             {0, 5},
    -- --             {-0.0125, 0.0125},
    -- --             {100, 450},
    -- --             {0, 3},
    -- --         },
    -- --         ExtraMinMaxLimits = {
    -- --             {-1, 1000000000},
    -- --             {-1, 20},
    -- --             {-0.12, 0.12},
    -- --             {-1, 5000},
    -- --             {0, 3},
    -- --         },
    -- --         RadialDomainLimits = {0, 500},
    -- --         CartesianDomainLimits = {
    -- --             {-300, 50},
    -- --             {-50, 50},
    -- --             {-50, 50},
    -- --         },
    -- --         LoadBinariesAtRuntime = true,
    -- --     },
    -- -- },

    -- -- {
    -- --     Name = "Flowlines_BATSRUS_Lutz_throughout",
    -- --     Parent = "GSMReferenceFrame",
    -- --     Renderable = {
    -- --         Type = "RenderableFieldlinesSequence",
    -- --         -- TracingMethod = "PreTracedJson",
    -- --         TracingMethod = "PreTracedBinary",
    -- --         -- SourceFolder = lutzJsonPath..'throughout/',
    -- --         SourceFolder = lutzFlowBinaryPath..'throughout/downsampled4/',
    -- --         -- SourceFolder = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/flow/throughout/',
    -- --         -- StartStateOffset = 92,
    -- --         -- StateStepSize = 100,
    -- --         -- MaxNumStates = 65,
    -- --         -- OutputLocationBinary = lutzFlowBinaryPath..'throughout/',
    -- --         ColorTablePaths = {
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    -- --         },
    -- --         ColorTableMinMax = {
    -- --             {0, 100000000},
    -- --             {0, 5},
    -- --             {-0.0125, 0.0125},
    -- --             {100, 450},
    -- --             {0, 3},
    -- --         },
    -- --         ExtraMinMaxLimits = {
    -- --             {-1, 1000000000},
    -- --             {-1, 20},
    -- --             {-0.12, 0.12},
    -- --             {-1, 5000},
    -- --             {0, 3},
    -- --         },
    -- --         RadialDomainLimits = {0, 500},
    -- --         CartesianDomainLimits = {
    -- --             {-300, 50},
    -- --             {-50, 50},
    -- --             {-50, 50},
    -- --         },
    -- --         LoadBinariesAtRuntime = true,
    -- --     },
    -- -- },
    -- -- {
    -- --     Name = "Flowlines_BATSRUS_Lutz_upstream",
    -- --     Parent = "GSMReferenceFrame",
    -- --     Renderable = {
    -- --         Type = "RenderableFieldlinesSequence",
    -- --         -- TracingMethod = "PreTracedJson",
    -- --         TracingMethod = "PreTracedBinary",
    -- --         -- SourceFolder = lutzJsonPath..'upstream/',
    -- --         -- SourceFolder = '/media/ccarlbau/64d3833e-0f62-4743-a83c-d831f1e3d08b/json/magnetic/model_run/flow/upstream/',
    -- --         SourceFolder = lutzFlowBinaryPath..'upstream/downsampled4/',
    -- --         -- StartStateOffset = 108,--108, -- 130 and forward ARE FINE!
    -- --         -- StateStepSize = 100,
    -- --         -- MaxNumStates = 15,--75,
    -- --         OutputLocationBinary = lutzFlowBinaryPath..'upstream/',
    -- --         ColorTablePaths = {
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    -- --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    -- --         },
    -- --         ColorTableMinMax = {
    -- --             {0, 100000000},
    -- --             {0, 5},
    -- --             {-0.0125, 0.0125},
    -- --             {100, 450},
    -- --             {0, 3},
    -- --         },
    -- --         ExtraMinMaxLimits = {
    -- --             {-1, 1000000000},
    -- --             {-1, 20},
    -- --             {-0.12, 0.12},
    -- --             {-1, 5000},
    -- --             {0, 3},
    -- --         },
    -- --         RadialDomainLimits = {0, 500},
    -- --         CartesianDomainLimits = {
    -- --             {-300, 50},
    -- --             {-50, 50},
    -- --             {-50, 50},
    -- --         },
    -- --         LoadBinariesAtRuntime = true,
    -- --     },
    -- -- },






    {
        Name = "Fieldlines_BATSRUS_EVENT_Asher-Fills",
        Parent = "GSMReferenceFrame",
        Renderable = {
            Type = "RenderableFieldlinesSequence",
            -- TracingMethod = "PreTracedJson",
            TracingMethod = "PreTracedBinary",
            -- SourceFolder = jsonFromAsher,
            -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/newfill/20120715_05/',
            SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/downsampled4/',
            -- SourceFolder = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/fullres/fills/downsampled1/',
            -- StartStateOffset = 1379,
            -- StateStepSize = 100,
            -- MaxNumStates = 61,
            -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_json/newfill/20120715_05/binaries/',
            -- OutputLocationBinary = '${OPENSPACE_DATA}/scene/fieldlinessequence/ashers_new_bats_binary/fullres/fills/',
            -- OutputLocationBinary = batsrusBinaryFolder,
            -- LoadBinariesAtRuntime = true,
            ColorTablePaths = {
                '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_transition.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
            },
            ColorTableMinMax = {
                {0, 1.3},
                {0, 60},
                {-0.0125, 0.0125},
                {-10, 10},
                {0, 3},
            },
            ExtraMinMaxLimits = {
                {-1, 10},
                {-1, 150},
                {-0.12, 0.12},
                {-10, 10},
                {0, 3},
            },
            RadialDomainLimits = {0, 500},
            CartesianDomainLimits = {
                {-300, 50},
                {-50, 50},
                {-50, 50},
            },
            LoadBinariesAtRuntime = true,
        },
    },

    {
        Name = "Fieldlines_BATSRUS_EVENT_Lutz_throughout",
        Parent = "GSMReferenceFrame",
        Renderable = {
            Type = "RenderableFieldlinesSequence",
            TracingMethod = "PreTracedBinary",
            SourceFolder = lutzEventMagneticBinary..'throughout/',
            -- StartStateOffset = 92,
            -- StateStepSize = 100,
            -- MaxNumStates = 65,
            ColorTablePaths = {
                '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
            },
            ColorTableMinMax = {
                {0, 100000000},
                {0, 5},
                {-0.0125, 0.0125},
                {100, 450},
                {0, 3},
            },
            ExtraMinMaxLimits = {
                {-1, 1000000000},
                {-1, 20},
                {-0.12, 0.12},
                {-1, 5000},
                {0, 3},
            },
            RadialDomainLimits = {0, 500},
            CartesianDomainLimits = {
                {-300, 50},
                {-50, 50},
                {-50, 50},
            },
            LoadBinariesAtRuntime = true,
        },
    },
    {
        Name = "Flowlines_BATSRUS_Lutz_EVENT_upstream2",
        Parent = "GSMReferenceFrame",
        Renderable = {
            Type = "RenderableFieldlinesSequence",
            TracingMethod = "PreTracedBinary",
            SourceFolder = lutzEventFlowBinary..'upstream/',
            -- StartStateOffset = 108,--108, -- 130 and forward ARE FINE!
            -- StateStepSize = 100,
            -- MaxNumStates = 15,--75,
            ColorTablePaths = {
                '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
            },
            ColorTableMinMax = {
                {0, 100000000},
                {0, 5},
                {-0.0125, 0.0125},
                {100, 450},
                {0, 3},
            },
            ExtraMinMaxLimits = {
                {-1, 1000000000},
                {-1, 20},
                {-0.12, 0.12},
                {-1, 5000},
                {0, 3},
            },
            RadialDomainLimits = {0, 500},
            CartesianDomainLimits = {
                {-300, 50},
                {-50, 50},
                {-50, 50},
            },
            LoadBinariesAtRuntime = true,
        },
    },















    -- -- -------------------------------------------------------------------------
    -- {
    --     Name = "Flowlines_BATSRUS_ARTIFICIAL_Lutz_user_selected",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         -- TracingMethod = "PreTracedJson",
    --         TracingMethod = "PreTracedBinary",
    --         -- SourceFolder = lutzJsonPath..'throughout/',
    --         -- SourceFolder = userSelected, -- lutzFlowBinaryPath..'throughout/downsampled4/',
    --         SourceFolder = lutzBinaryPath, -- lutzFlowBinaryPath..'throughout/downsampled4/',
    --         -- StartStateOffset = 92,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 65,
    --         -- OutputLocationBinary = lutzBinaryPath,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },
    -- -------------------------------------------------------------------------
    {
        Name = "Fieldlines_BATSRUS_EVENT_Lutz_open-closed",
        Parent = "GSMReferenceFrame",
        Renderable = {
            Type = "RenderableFieldlinesSequence",
            TracingMethod = "PreTracedBinary",
            SourceFolder = lutzEventMagneticBinary..'open-closed/',
            -- StartStateOffset = 515,
            -- StateStepSize = 100,
            -- MaxNumStates = 55,
            ColorTablePaths = {
                '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
                '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
            },
            ColorTableMinMax = {
                {0, 100000000},
                {0, 5},
                {-0.0125, 0.0125},
                {100, 450},
                {0, 3},
            },
            ExtraMinMaxLimits = {
                {-1, 1000000000},
                {-1, 20},
                {-0.12, 0.12},
                {-1, 5000},
                {0, 3},
            },
            RadialDomainLimits = {0, 500},
            CartesianDomainLimits = {
                {-300, 50},
                {-50, 50},
                {-50, 50},
            },
            LoadBinariesAtRuntime = true,
        },
    },

    --     {
    --     Name = "Fieldlines_BATSRUS_EVENT_Lutz_throughout",
    --     Parent = "GSMReferenceFrame",
    --     Renderable = {
    --         Type = "RenderableFieldlinesSequence",
    --         TracingMethod = "PreTracedBinary",
    --         SourceFolder = lutzEventMagneticBinary..'throughout/',
    --         -- StartStateOffset = 2190,
    --         -- StateStepSize = 100,
    --         -- MaxNumStates = 55,
    --         ColorTablePaths = {
    --             '${OPENSPACE_DATA}/colortables/batsrus_temperature.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_density.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_current.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_velocity.txt',
    --             '${OPENSPACE_DATA}/colortables/batsrus_topology.txt',
    --         },
    --         ColorTableMinMax = {
    --             {0, 100000000},
    --             {0, 5},
    --             {-0.0125, 0.0125},
    --             {100, 450},
    --             {0, 3},
    --         },
    --         ExtraMinMaxLimits = {
    --             {-1, 1000000000},
    --             {-1, 20},
    --             {-0.12, 0.12},
    --             {-1, 5000},
    --             {0, 3},
    --         },
    --         RadialDomainLimits = {0, 500},
    --         CartesianDomainLimits = {
    --             {-300, 50},
    --             {-50, 50},
    --             {-50, 50},
    --         },
    --         LoadBinariesAtRuntime = true,
    --     },
    -- },




}
