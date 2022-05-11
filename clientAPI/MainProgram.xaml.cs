﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text.Json;
using clientAPI.Requests_and_Responses;
using clientAPI.JsonHelpers;
using clientAPI;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for MainProgram.xaml
    /// </summary>
    public partial class MainProgram : Window
    {
        public static Client appClient;
        public static string mainUser;

        public MainProgram()
        {

            load(this, null);

            appClient = new Client("127.0.0.1", 8200);
            //InitializeComponent();
            LoginWindow loginWindow = new LoginWindow();
            loginWindow.Show();
            Hide();
        }

        private void load(object sender, EventArgs e)
        {
            AllocConsole();
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
    }
}
