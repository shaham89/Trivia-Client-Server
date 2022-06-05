﻿using clientAPI.Create_and_Join;
using clientAPI.Login_and_Signup;
using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using clientAPI.GameFolder;

static class constants
{
    public const int MAXQUESTIONS = 10;
}

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {

        public CreateRoom()
        {

            InitializeComponent();
        }

        private void clickExit(object sender, RoutedEventArgs e)
        {
            
            menu menu = new menu(MainProgram.MainUsername);
            menu.WindowStartupLocation = WindowStartupLocation.CenterScreen;

            menu.Show();
            this.Close();
        }

        private void clickCreate(object sender, RoutedEventArgs e)
        {
            uint players = Convert.ToUInt32(Players.Text);
            uint time = Convert.ToUInt32(Time.Text);

            CreateRoomRequest createRoomRequest = new CreateRoomRequest(roomName.Text, players, constants.MAXQUESTIONS, time);

            
            Console.Write(createRoomRequest);
            byte[] data = JsonHelpers.JsonFormatSerializer.createSerializer(createRoomRequest);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.CREATE_ROOM_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            
            CreateRoomResponse createRoomResponse = JsonHelpers.JsonFormatDeserializer.CreateRoomResponseDeserializer(returnMsg.Message);
           
            //login failed
            if (createRoomResponse.Status == Response.status_error)
            {
                Console.Write("NOPE room BAD ROOM");
                return;
            }
            
            Console.Write("Createed room succesfully");
           

            RoomData metaData = new RoomData(0, roomName.Text, players, constants.MAXQUESTIONS, time, false);

            WaitingRoom waitingRoom = new WaitingRoom(metaData, true);
            waitingRoom.WindowStartupLocation = WindowStartupLocation.CenterScreen;

            waitingRoom.Show();
            Close();

        }

        private void previewTextInput(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }
    }
}
