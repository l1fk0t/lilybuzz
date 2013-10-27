namespace MitersquareApp
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Device.Location;
    using System.IO;
    using System.Linq;
    using System.Net;
    using System.Net.Http;
    using System.Security.Cryptography;
    using System.Text;
    using System.Threading.Tasks;

    using Newtonsoft.Json;

    public static class FoursquareClient
    {
        private const string ClientId = "IHVFV1ALBTSPWGIMHNRCR4GBUDLLGULWRACJ5A5RO544MXLD";

        private const string ClientSecret = "0W10IUXDTVFKAQC4P4ORI1ODJ45JOMXYHEBZE25DHRL0JAU0";

        private const string Url = "https://api.foursquare.com/v2/venues/search?v=20131016&client_id={0}&client_secret={1}&ll={2}&categoryId=4d4b7105d754a06376d81259&limit=8&intent=checkin&radius=1500";

        public async static Task<IEnumerable<VenueViewModel>> GetVenuesByLocation(GeoCoordinate coordinate)
        {
            string latLong = coordinate.ToString();
            var url = string.Format(Url, ClientId, ClientSecret, latLong);

            var client = new HttpClient();
            var json = await client.GetStringAsync(url);
            
            var data = JsonConvert.DeserializeObject<FoursquareResponse>(json);

            return data.response.venues.Select(v =>
                {
                    var c = v.categories.First();
                    return new VenueViewModel()
                           {
                               Name = v.name, 
                               IconUrl = c.icon.prefix + "64" + c.icon.suffix,
                               Coordinate = new GeoCoordinate(v.location.lat, v.location.lng)
                           };
                });
        }
    }

    public class VenueViewModel
    {
        public string Name { get; set; }

        public string IconUrl { get; set; }
        public GeoCoordinate Coordinate { get; set; }
    }

    public class FoursquareResponse
    {
        public Response response { get; set; }
        public Meta meta { get; set; }
    }

    public class Response
    {
        public object[] neighborhoods { get; set; }
        public Venue[] venues { get; set; }
    }

    public class Venue
    {
        public Herenow hereNow { get; set; }
        public Specials specials { get; set; }
        public Location location { get; set; }
        public string referralId { get; set; }
        public Stats stats { get; set; }
        public string name { get; set; }
        public Category[] categories { get; set; }
        public Contact contact { get; set; }
        public bool restricted { get; set; }
        public string url { get; set; }
        public string id { get; set; }
        public bool verified { get; set; }
        public string storeId { get; set; }
        public Events events { get; set; }
    }

    public class Herenow
    {
        public int count { get; set; }
        public Group[] groups { get; set; }
    }

    public class Group
    {
        public int count { get; set; }
        public string name { get; set; }
        public string type { get; set; }
        public object[] items { get; set; }
    }

    public class Specials
    {
        public int count { get; set; }
        public object[] items { get; set; }
    }

    public class Location
    {
        public string country { get; set; }
        public int distance { get; set; }
        public float lat { get; set; }
        public string crossStreet { get; set; }
        public string state { get; set; }
        public string city { get; set; }
        public string cc { get; set; }
        public string address { get; set; }
        public float lng { get; set; }
        public string postalCode { get; set; }
    }

    public class Stats
    {
        public int usersCount { get; set; }
        public int tipCount { get; set; }
        public int checkinsCount { get; set; }
    }

    public class Contact
    {
        public string phone { get; set; }
        public string formattedPhone { get; set; }
        public string twitter { get; set; }
    }

    public class Events
    {
        public int count { get; set; }
        public string summary { get; set; }
        public Item[] items { get; set; }
    }

    public class Item
    {
        public Provider provider { get; set; }
        public string timeZone { get; set; }
        public object[] images { get; set; }
        public int date { get; set; }
        public Stats stats { get; set; }
        public string name { get; set; }
        public Category[] categories { get; set; }
        public Participant[] participants { get; set; }
        public string text { get; set; }
        public string url { get; set; }
        public string id { get; set; }
        public bool allDay { get; set; }
        public int startAt { get; set; }
        public int endAt { get; set; }
    }

    public class Provider
    {
        public string urlText { get; set; }
        public Iconurl iconUrl { get; set; }
        public string name { get; set; }
    }

    public class Iconurl
    {
        public string name { get; set; }
        public int[] sizes { get; set; }
        public string prefix { get; set; }
    }

    public class Category
    {
        public Icon icon { get; set; }
        public bool primary { get; set; }
        public string name { get; set; }
        public string id { get; set; }
        public string shortName { get; set; }
        public string pluralName { get; set; }
    }

    public class Icon
    {
        public string suffix { get; set; }
        public string prefix { get; set; }
    }

    public class Participant
    {
        public Participant participant { get; set; }
        public string role { get; set; }
    }

    public class Meta
    {
        public int code { get; set; }
    }
}
