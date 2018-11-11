// Cloud iot details.
const char *project_id = "soilsense-system";
const char *location = "us-central1";
const char *registry_id = "soil";
const char *device_id = "device_1";
const char *private_key_str =
    "35:9f:a1:a3:0e:2d:c7:90:5d:4d:88:58:2a:85:ff:"
    "af:e1:52:28:a9:7f:a4:9c:e1:e6:64:ce:ce:73:2b:"
    "32:b5";
const char *root_cert =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIE+zCCA+OgAwIBAgIIY3yFXHEKoNEwDQYJKoZIhvcNAQELBQAwVDELMAkGA1UE\n"
    "BhMCVVMxHjAcBgNVBAoTFUdvb2dsZSBUcnVzdCBTZXJ2aWNlczElMCMGA1UEAxMc\n"
    "R29vZ2xlIEludGVybmV0IEF1dGhvcml0eSBHMzAeFw0xODEwMzAxMzE0MDBaFw0x\n"
    "OTAxMjIxMzE0MDBaMG0xCzAJBgNVBAYTAlVTMRMwEQYDVQQIDApDYWxpZm9ybmlh\n"
    "MRYwFAYDVQQHDA1Nb3VudGFpbiBWaWV3MRMwEQYDVQQKDApHb29nbGUgTExDMRww\n"
    "GgYDVQQDDBNtcXR0Lmdvb2dsZWFwaXMuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOC\n"
    "AQ8AMIIBCgKCAQEAwnF0XwGnqhXp/AP3Y2qYCxc4Yzvm+nw5co3omFPnpHI9cE9x\n"
    "vBTdx34/5ZditzwPff8lkSP38hk6ZQgiIP8ZuAo7VNJ4mGIqkSshfMWKaxsTRkMB\n"
    "vw58JJfPyFN4XM5ge9TOCRyumHDUs333lPejG6Xt21jN5m4pZv6VGDvs2XnUJdqK\n"
    "+vhmCTRF/fQC3K/dHJfZapMY61iN6HDNOWY30+oW8dradITPlnFsnlx5MKCxYzeK\n"
    "ZxaaSIujJhEmWIbta8QlaIYu8oHHEZ2Ntkc2TZOxh27OLd81JEIIWqdsdWs/ZKxt\n"
    "RogfQLiTUN7XGC3N2LkUV6D/LpWJK0vjE29czQIDAQABo4IBtjCCAbIwEwYDVR0l\n"
    "BAwwCgYIKwYBBQUHAwEwgYwGA1UdEQSBhDCBgYITbXF0dC5nb29nbGVhcGlzLmNv\n"
    "bYIjbXF0dC1wcmVwcm9kLnNhbmRib3guZ29vZ2xlYXBpcy5jb22CI21xdHQtc3Rh\n"
    "Z2luZy5zYW5kYm94Lmdvb2dsZWFwaXMuY29tgiBtcXR0LXRlc3Quc2FuZGJveC5n\n"
    "b29nbGVhcGlzLmNvbTBoBggrBgEFBQcBAQRcMFowLQYIKwYBBQUHMAKGIWh0dHA6\n"
    "Ly9wa2kuZ29vZy9nc3IyL0dUU0dJQUczLmNydDApBggrBgEFBQcwAYYdaHR0cDov\n"
    "L29jc3AucGtpLmdvb2cvR1RTR0lBRzMwHQYDVR0OBBYEFM4sFsWMF90T0qiEvDqw\n"
    "thpCVDEOMAwGA1UdEwEB/wQCMAAwHwYDVR0jBBgwFoAUd8K4UJpndnaxLcKG0IOg\n"
    "fqZ+ukswIQYDVR0gBBowGDAMBgorBgEEAdZ5AgUDMAgGBmeBDAECAjAxBgNVHR8E\n"
    "KjAoMCagJKAihiBodHRwOi8vY3JsLnBraS5nb29nL0dUU0dJQUczLmNybDANBgkq\n"
    "hkiG9w0BAQsFAAOCAQEASR3o6p72glGV7zukVQCdyfe2fD/49zT4xV477YpRd7Ux\n"
    "LT7MEU8EW286veFSuDfTaBjQ8UsAKCO+Xsy3WjQQ7S9sug286aTGfvJIhu1tS8yO\n"
    "rvl8BYAGKy2vfdFMCom38DQhjGMvTGUgO/Y22Ivx8zb81SC2hMeXdlajIgS7WXSQ\n"
    "4zHjgBGUAOUF+N+0cZ9rEP2aA1xvgrNIWybJVwgYyirLeeaxCUW2+y5o8fVoViYx\n"
    "uos8d5Y7hAXwKB1SlooiEHMiCCKcw3kLN5pFOSL7SeavWP6aPFAT6FAs475ltk1N\n"
    "djybk+c+o6+5V83cPcqFl97QUaylmBaaT51Kx51O+w==\n"
    "-----END CERTIFICATE-----\n"
