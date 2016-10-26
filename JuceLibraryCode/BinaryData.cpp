/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== saw.dsp ==================
static const unsigned char temp_binary_data_0[] =
"import(\"stdfaust.lib\");\n"
"frequency = nentry(\"freq\",440,20,20000,0.01) : si.smoo;\n"
"level = nentry(\"gain\",1,0,1,0.01) : si.smoo;\n"
"onoff = button(\"gate\") : si.smoo;\n"
"process = hgroup(\"saw\",os.sawtooth(frequency) * level * onoff);";

const char* saw_dsp = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x6fac546b:  numBytes = 222; return saw_dsp;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "saw_dsp"
};

}
