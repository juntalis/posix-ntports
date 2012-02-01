using System;

namespace Common
{
	[Serializable]
	public abstract class CommandLineException : Exception
	{
		protected CommandLineException() { }
		protected CommandLineException(string message) : base(message) { }
		protected CommandLineException(string message, Exception inner) : base(message, inner) { }
		protected CommandLineException(
			System.Runtime.Serialization.SerializationInfo info,
			System.Runtime.Serialization.StreamingContext context)
			: base(info, context) { }
	}


	[Serializable]
	public class ValidationException : CommandLineException
	{
		public ValidationException(string message) : base(message) { }
		public ValidationException(string message, Exception inner) : base(message, inner) { }
		protected ValidationException(
			System.Runtime.Serialization.SerializationInfo info,
			System.Runtime.Serialization.StreamingContext context)
			: base(info, context) { }
	}

	/// <summary>
	/// Validation on the parameter's value
	/// </summary>
	[Serializable]
	[AttributeUsage(AttributeTargets.Property, AllowMultiple = true)]
	public abstract class ValidationAttribute : Attribute
	{
		/// <summary>
		/// The validator
		/// </summary>
		public IPropertyValidator Validator { get; private set; }

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="validator">The validator</param>
		protected ValidationAttribute(IPropertyValidator validator)
		{
			Validator = validator;
		}

		/// <summary>
		/// The description of this validation attribute, used when asking for help
		/// </summary>
		public virtual string Description
		{
			get { return GetType().Name; }
		}
	}

	/// <summary>
	/// A value validator
	/// </summary>
	public interface IPropertyValidator
	{
		/// <summary>
		/// Validate the value
		/// </summary>
		void Validate(object value);
	}
}