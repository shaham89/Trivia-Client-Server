﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Requests_and_Responses
{
	internal class Response
	{

        public uint status;
        public const uint status_ok = 2;
		public const uint status_error = 5;

        public Response(uint status)
        {
            this.status = status;
        }
		public uint Status { get; set; }

    }
    internal class LoginResponse : Response
    {
        public LoginResponse(uint status) : base(status)
        {
			
        }
		
	};
	internal class SignUpResponse : Response
	{
		public SignUpResponse(uint status) : base(status)
		{

		}

	};

	internal class  ErrorResponse
	{
		string message;

        public ErrorResponse(string message)
        {
            this.message = message;
        }
		public string Message { get; set; } = default!;
    };
	internal class LogOutResponse : Response
	{
		public LogOutResponse(uint status) : base(status)
		{

		}

	};

	//internal class  GetRoomsResponse :  Response
	//{
	//	vector<Room> rooms;
	//};

	internal class  GetPlayersInRoomResponse
	{
		List<string> players;

        public GetPlayersInRoomResponse(List<string> players)
        {
            this.players = players;
        }
		public List<string> Players { get; set; }
    }
    internal class  GetHighScoreResponse : Response
	{
		List<string> statistics;

        public GetHighScoreResponse(List<string> statistics,uint status) :base (status)
        {
            this.statistics = statistics;
        }

        public List<string> highest { get;set; }

       
       
	};
	internal class  GetPersonalStatsResponse :  Response
	{
		List<string> statistics;

        public GetPersonalStatsResponse(List<string> statistics, uint status) :base(status)
        {
            this.statistics = statistics;
        }
    }
    internal class JoinRoomResponse : Response
    {
        public JoinRoomResponse(uint status) : base(status)
        {
        }
    }
    internal class CreateRoomResponse : Response
    {
        public CreateRoomResponse(uint status) : base(status)
        {
        }
    }
}
