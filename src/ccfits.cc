#include "fits.h"
#include "hdu.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Fits::GetClass(env, exports);
    Hdu::GetClass(env, exports);

    return exports;
}

NODE_API_MODULE(addon, Init)
