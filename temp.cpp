#include <"coreclrhost.h">
using System;


int main(){
    void *coreclr = dlopen("libcoreclr.dylib", RTLD_NOW | RTLD_LOCAL);

     coreclr_initialize_ptr coreclr_init = reinterpret_cast<coreclr_initialize_ptr>(dlsym(coreclr, "coreclr_initialize"));

    string tpa_list;
    AddFilesFromDirectoryToTpaList(exe_path, tpa_list);

    const char *property_keys[] = {
        "APP_PATHS",
        "TRUSTED_PLATFORM_ASSEMBLIES"
    };
    
    const char *property_values[] = {
        // APP_PATHS
        app_path,
        // TRUSTED_PLATFORM_ASSEMBLIES
        tpa_list.c_str()
    };

    int ret = coreclr_init(
        app_path,                               // exePath
        "host",                                 // appDomainFriendlyName
        sizeof(property_values)/sizeof(char *), // propertyCount
        property_keys,                          // propertyKeys
        property_values,                        // propertyValues
        &coreclr_handle,                        // hostHandle
        &domain_id                              // domainId
    ); 


}


public class ManLib
{
    public static string Bootstrap()
    {
        typedef char *(*bootstrap_ptr)();

        bootstrap_ptr dele;
        ret = coreclr_create_dele(
            coreclr_handle,
            domain_id,
            "manlib",
            "ManLib",
            "Bootstrap",
            reinterpret_cast<void **>(&dele)
            ); 

        char *msg = dele();
        cout << "ManLib::Bootstrap() returned " << msg << endl;    
        free(msg);

        return "Bootstrap!";
    }
}
